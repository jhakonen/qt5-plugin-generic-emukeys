#ifndef EMUKEYSHANDLER_H
#define EMUKEYSHANDLER_H

#include <QObject>

class EmuKeysHandler : public QObject
{
    Q_OBJECT
public:
    explicit EmuKeysHandler(const QString &specification, QObject *parent = 0);

signals:

public slots:

};

#endif // EMUKEYSHANDLER_H
