#include "keysender.h"
#include <QDebug>

KeySender::KeySender(QObject *parent)
    : QObject(parent) {
}

void KeySender::sendKeyEvent(const QString &name, bool pressed) {
    qDebug() << "SENDING KEY: " << name << ", PRESSED: " << pressed;
}
