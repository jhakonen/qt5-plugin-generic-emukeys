#include <QtGui/QGuiApplication>
#include <QQuickItem>
#include <QTimer>
#include "qtquick2applicationviewer.h"
#include "keysource.h"

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

    return app.exec();
}
