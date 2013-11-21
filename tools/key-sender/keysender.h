#ifndef KEYSENDER_H
#define KEYSENDER_H

#include <QObject>

class KeySender : public QObject {
    Q_OBJECT
public:
    KeySender(QObject *parent = 0);

public slots:
    void sendKeyEvent(const QString &name, bool pressed);
};

#endif // KEYSENDER_H
