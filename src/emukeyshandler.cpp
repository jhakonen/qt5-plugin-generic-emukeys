#include "emukeyshandler.h"
#include <QDebug>
#include <QTimer>
#include <QKeyEvent>
#include <QGuiApplication>

#include <qpa/qwindowsysteminterface.h>

QWindow *getTargetWindow() {
    auto window = QGuiApplication::focusWindow();
    // with debug build get at least one window, as a result, the key events
    // are sent even if none of the application's windows have focus
#ifndef QT_NO_DEBUG
    if (!window) {
        auto list = QGuiApplication::allWindows();
        if (list.count()) {
            window = list[0];
        }
    }
#endif
    return window;
}

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
        QWindowSystemInterface::handleKeyEvent(getTargetWindow(),
            getRandomKeyState(), getRandomKey(), Qt::NoModifier);
    });
    fooTimer->setInterval(1000);
    fooTimer->start();
}

EmuKeysHandler::EmuKeysHandler(const QString &specification, QObject *parent)
    : QObject(parent) {
    Q_UNUSED(specification);

    sendFakeKeyEvents();
}
