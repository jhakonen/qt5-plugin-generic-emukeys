#include "keysender.h"
#include <QDebug>
#include <QTimer>
#include <QTcpSocket>
#include <QDataStream>
#include <functional>

KeySender::KeySender(QObject *parent)
    : QObject(parent) {
    mConnected = false;
    mHost = "localhost";

    mReconnectTimer = new QTimer(this);
    mReconnectTimer->setSingleShot(true);
    mReconnectTimer->setInterval(1000);
    connect(mReconnectTimer.data(), &QTimer::timeout, [this]() {
        setConnected(false);
        connectToHost();
    });

    mConnection = new QTcpSocket(this);

    connect(mConnection.data(), &QTcpSocket::connected, [this]() {
        setConnected(true);
    });
    connect(mConnection.data(), &QTcpSocket::disconnected, [this]() {
        setConnected(false);
        reconnect();
    });
    connect(mConnection.data(), static_cast<void(QTcpSocket::*)(QAbstractSocket::SocketError)>(&QTcpSocket::error), [this](QAbstractSocket::SocketError) {
        setConnected(false);
        reconnect();
    });

    mStream = new QDataStream(mConnection);
    mStream->setVersion(QDataStream::Qt_4_8);
}

KeySender::~KeySender() {
    mConnection->close();
    delete mStream;
}

bool KeySender::isConnected() const {
    return mConnected;
}

void KeySender::setHost(const QString &host) {
    mHost = host;
    qDebug() << "SET HOST TO" << host;
    reconnect();
}

void KeySender::sendKeyEvent(const QString &name, bool pressed) {
    if (mConnected) {
        qDebug() << "SENDING KEY: " << name << ", PRESSED: " << pressed;
        QString msg = "key-event:" + name + ":" + (pressed? "1": "0");
        QByteArray data = msg.toUtf8();
        quint16 size = data.length();
        *mStream << size;
        mStream->writeRawData(data, size);
    }
}

void KeySender::setConnected(bool newState) {
    if (mConnected != newState) {
        mConnected = newState;
        emit connectedChanged();
    }
}

void KeySender::reconnect() {
    if (!mReconnectTimer->isActive()) {
        mReconnectTimer->start();
    }
}

void KeySender::connectToHost() {
    qDebug() << "Connecting...";
    setConnected(false);
    mConnection->close();
    mConnection->connectToHost(mHost, 7856);
}
