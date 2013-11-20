#include "emukeyshandler.h"

EmuKeysHandler::EmuKeysHandler(const QString &specification, QObject *parent)
    : QObject(parent) {
    Q_UNUSED(specification);
}
