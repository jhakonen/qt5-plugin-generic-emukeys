#include "emukeysplugin.h"
#include "emukeyshandler.h"

EmuKeysPlugin::EmuKeysPlugin() :
    QGenericPlugin() {
}

QObject *EmuKeysPlugin::create(const QString &key, const QString &specification) {
    if (key.compare("EmuKeys", Qt::CaseInsensitive) == 0) {
        return new EmuKeysHandler(specification);
    }
    return nullptr;
}

#if QT_VERSION < 0x050000
Q_EXPORT_PLUGIN2(qt5-plugin-generic-emukeys, EmuKeysPlugin)
#endif // QT_VERSION < 0x050000
