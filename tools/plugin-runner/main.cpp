#include <QtGui/QGuiApplication>
#include <QQuickView>
#include <QQuickItem>
#include <QQmlContext>
#include <QUrl>

#include "keysource.h"

int main(int argc, char *argv[]) {
    QGuiApplication app(argc, argv);
    KeySource keySource(&app);
    QQuickView viewer;

    viewer.rootContext()->setContextProperty("keySource", &keySource);
    viewer.setSource(QUrl("qrc:/main.qml"));
    viewer.show();

    return app.exec();
}
