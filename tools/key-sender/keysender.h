#ifndef KEYSENDER_H
#define KEYSENDER_H

#include <QObject>
#include <QPointer>

class QDataStream;
class QTcpSocket;
class QTimer;

class KeySender : public QObject {
    Q_OBJECT
    Q_PROPERTY(bool connected READ isConnected NOTIFY connectedChanged)

public:
    KeySender(QObject *parent = 0);
    ~KeySender();

    bool isConnected() const;
    void connectToHost();

public slots:
    void setHost(const QString &host);
    void sendKeyEvent(const QString &name, bool pressed);

signals:
    void connectedChanged();

private:
    void setConnected(bool newState);
    void reconnect();

    bool mConnected;
    QString mHost;
    QPointer<QTimer> mReconnectTimer;
    QPointer<QTcpSocket> mConnection;
    QDataStream *mStream;
};

#endif // KEYSENDER_H
