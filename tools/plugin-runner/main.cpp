#include <QtGui/QGuiApplication>
#include <QQuickItem>
#include <QTimer>
#include <QKeyEvent>
#include "qtquick2applicationviewer.h"
#include "keysource.h"

QEvent::Type getRandomKeyState() {
    return (qrand() % 2)? QEvent::KeyPress: QEvent::KeyRelease;
}

int getRandomKey() {
    switch (qrand() % 3) {
    case 0:
        return Qt::Key_VolumeDown;
    case 1:
        return Qt::Key_VolumeUp;
    case 2:
        return Qt::Key_PowerOff;
    }
}

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QtQuick2ApplicationViewer viewer;
    viewer.setMainQmlFile(QStringLiteral("qml/plugin-runner/main.qml"));
    viewer.showExpanded();

    KeySource keySource(&app);

    auto getObjectByName = [&](const QString &name)->QObject* {
        return viewer.rootObject()->findChild<QObject*>(name);
    };

    auto power = getObjectByName("power");
    auto volumeDown = getObjectByName("volumeDown");
    auto volumeUp = getObjectByName("volumeUp");

    power->connect(&keySource, &KeySource::powerKeyReceived, [&](bool pressed) {
        QMetaObject::invokeMethod(power, "flash");
        power->setProperty("isPressed", pressed);
    });
    volumeDown->connect(&keySource, &KeySource::volumeDownKeyReceived, [&](bool pressed) {
        QMetaObject::invokeMethod(volumeDown, "flash");
        volumeDown->setProperty("isPressed", pressed);
    });
    volumeUp->connect(&keySource, &KeySource::volumeUpKeyReceived, [&](bool pressed) {
        QMetaObject::invokeMethod(volumeUp, "flash");
        volumeUp->setProperty("isPressed", pressed);
    });

    // fakey sending of events
    QTimer fooTimer;
    QObject::connect(&fooTimer, &QTimer::timeout, [&]() {
        QGuiApplication::sendEvent(&app, new QKeyEvent(getRandomKeyState(), getRandomKey(), Qt::NoModifier));
    });
    fooTimer.setInterval(1000);
    fooTimer.start();

    return app.exec();
}
