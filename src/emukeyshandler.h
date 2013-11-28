#ifndef EMUKEYSHANDLER_H
#define EMUKEYSHANDLER_H

#include <QObject>
#include <QPointer>

class QTcpServer;
class QTcpSocket;

class EmuKeysHandler : public QObject
{
    Q_OBJECT
public:
    explicit EmuKeysHandler(const QString &specification, QObject *parent = 0);

signals:

public slots:

private:
    void handleConnection(QTcpSocket *connection);
    void handleKeyEvent(const QString &name, bool pressed);

    QPointer<QTcpServer> mServer;
};

#endif // EMUKEYSHANDLER_H
