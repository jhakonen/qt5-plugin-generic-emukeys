#include "keysource.h"
#include <QKeyEvent>

KeySource::KeySource(QObject *eventSource, QObject *parent)
    : QObject(parent) {
    Q_ASSERT(eventSource);
    eventSource->installEventFilter(this);
}

bool KeySource::eventFilter(QObject *obj, QEvent *event) {
    if (event->type() == QEvent::KeyPress || event->type() == QEvent::KeyRelease) {
        bool pressed = event->type() == QEvent::KeyPress;
        auto keyEvent = static_cast<QKeyEvent *>(event);

        switch (keyEvent->key()) {
        case Qt::Key_VolumeDown:
            emit volumeDownKeyReceived(pressed);
            break;

        case Qt::Key_VolumeUp:
            emit volumeUpKeyReceived(pressed);
            break;

        case Qt::Key_PowerOff:
            emit powerKeyReceived(pressed);
            break;

        default:
            break;
        }
    }
    return false;
}
