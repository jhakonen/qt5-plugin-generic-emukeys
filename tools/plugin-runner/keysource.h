#ifndef KEYSOURCE_H
#define KEYSOURCE_H

#include <QObject>

class KeySource : public QObject {
    Q_OBJECT
public:
    KeySource(QObject *eventSource, QObject *parent = 0);

    virtual bool eventFilter(QObject *obj, QEvent *event);

signals:
    void powerKeyReceived(bool pressed);
    void volumeUpKeyReceived(bool pressed);
    void volumeDownKeyReceived(bool pressed);
};

#endif // KEYSOURCE_H
