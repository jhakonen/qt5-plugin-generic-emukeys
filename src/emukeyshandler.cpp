#include "emukeyshandler.h"
#include <QDebug>
#include <QTimer>
#include <QKeyEvent>
#include <QGuiApplication>
#include <QTcpServer>
#include <QTcpSocket>
#include <QByteArray>

#include <qpa/qwindowsysteminterface.h>

#include <functional>

QWindow *getTargetWindow() {
    auto window = QGuiApplication::focusWindow();
    // with debug build get at least one window, as a result, the key events
    // are sent even if none of the application's windows have focus
//#ifndef QT_NO_DEBUG
    if (!window) {
        auto list = QGuiApplication::allWindows();
        if (list.count()) {
            window = list[0];
        }
    }
//#endif
    return window;
}

int keyNameToKey(const QString &name) {
    static QMap<QString,int> map;
    if (map.isEmpty()) {
        map["power-off"] = Qt::Key_PowerOff;
        map["volume-down"] = Qt::Key_VolumeDown;
        map["volume-up"] = Qt::Key_VolumeUp;
    }
    Q_ASSERT(map.contains(name));
    return map[name];
}

class MessageReader {
public:
    MessageReader(QTcpSocket *connection, std::function<void(QByteArray)> callback)
        : connection(connection), callback(callback) {
        QObject::connect(connection, &QTcpSocket::readyRead, [this]() {
            handleReadyRead();
        });

        handler = std::bind(&MessageReader::handleSize, this);
    }

    void handleReadyRead() {
        while (connection->bytesAvailable()) {
            handler();
        }
    }

    void handleSize() {
        if (connection->bytesAvailable() >= sizeof(messageSize)) {
            auto data = connection->read(2);
            QDataStream stream(&data, QIODevice::ReadOnly);
            stream >> messageSize;
            qDebug() << "MESSAGE SIZE:" << messageSize;
            handler = std::bind(&MessageReader::handleMessage, this);
        }
    }

    void handleMessage() {
        if (connection->bytesAvailable()) {
            message += connection->read(messageSize - message.size());

            if (message.size() == messageSize) {
                callback(message);
                message.clear();
                handler = std::bind(&MessageReader::handleSize, this);
            }
        }
    }

    QTcpSocket *connection;
    std::function<void(QByteArray)> callback;
    std::function<void()> handler;
    quint16 messageSize;
    QByteArray message;
};

EmuKeysHandler::EmuKeysHandler(const QString &specification, QObject *parent)
    : QObject(parent) {
    Q_UNUSED(specification);

    mServer = new QTcpServer(this);
    mServer->listen(QHostAddress::Any, 7856);

    connect(mServer.data(), &QTcpServer::newConnection, [this]() {
        handleConnection(mServer->nextPendingConnection());
    });
}

void EmuKeysHandler::handleConnection(QTcpSocket *connection) {
    Q_ASSERT(connection);
    qDebug() << "New connection received";
    new MessageReader(connection, [this](const QByteArray &message) {
        qDebug() << "Received message:" << message.toHex();
        auto msgStr = QString::fromUtf8(message);
        auto parts = msgStr.split(':');
        Q_ASSERT(parts.length());

        if (parts[0] == "key-event" && parts.length() == 3) {
            handleKeyEvent(parts[1], parts[2].toInt());
        } else {
            Q_ASSERT(false);
        }

    });
}

void EmuKeysHandler::handleKeyEvent(const QString &name, bool pressed) {
    auto type = pressed? QEvent::KeyPress: QEvent::KeyRelease;
    QWindowSystemInterface::handleKeyEvent(getTargetWindow(),
        type, keyNameToKey(name), Qt::NoModifier);
}
