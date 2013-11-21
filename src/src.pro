QT       += core gui-private

TARGET = qt5-plugin-generic-emukeys

PLUGIN_TYPE = generic
PLUGIN_CLASS_NAME = EmuKeysPlugin
load(qt_plugin)

DESTDIR = ../build/generic

SOURCES += emukeysplugin.cpp \
    emukeyshandler.cpp

HEADERS += emukeysplugin.h \
    emukeyshandler.h
OTHER_FILES += emukeys.json

unix {
    target.path = /usr/lib
    INSTALLS += target
}
