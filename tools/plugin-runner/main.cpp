#include <QtGui/QGuiApplication>
#include <QQuickItem>
#include <QTimer>
#include <QKeyEvent>
#include <QQmlContext>

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
    return 0;
}

void sendFakeKeyEvents() {
    auto fooTimer = new QTimer;
    QObject::connect(fooTimer, &QTimer::timeout, []() {
        QCoreApplication::sendEvent(QCoreApplication::instance(),
            new QKeyEvent(getRandomKeyState(), getRandomKey(), Qt::NoModifier));
    });
    fooTimer->setInterval(1000);
    fooTimer->start();
}

int main(int argc, char *argv[]) {
    QGuiApplication app(argc, argv);
    KeySource keySource(&app);
    QtQuick2ApplicationViewer viewer;

    viewer.rootContext()->setContextProperty("keySource", &keySource);
    viewer.setMainQmlFile(QStringLiteral("qml/plugin-runner/main.qml"));
    viewer.showExpanded();

    sendFakeKeyEvents();

    return app.exec();
}
