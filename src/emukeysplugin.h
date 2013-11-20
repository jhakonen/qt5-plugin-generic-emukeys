#ifndef EMUKEYSPLUGIN_H
#define EMUKEYSPLUGIN_H

#include <QGenericPlugin>


class EmuKeysPlugin : public QGenericPlugin {
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QGenericPluginFactoryInterface" FILE "emukeys.json")

public:
    EmuKeysPlugin();
    virtual QObject *create(const QString &key, const QString &specification);
};

#endif // EMUKEYSPLUGIN_H
