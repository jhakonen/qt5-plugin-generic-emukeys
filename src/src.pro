QT       += core

TARGET = qt5-plugin-generic-emukeys
TEMPLATE = lib
CONFIG += plugin

#DESTDIR = $$[QT_INSTALL_PLUGINS]/codecs
DESTDIR = ../build

SOURCES += emukeysplugin.cpp \
    emukeyshandler.cpp

HEADERS += emukeysplugin.h \
    emukeyshandler.h
OTHER_FILES += emukeys.json

unix {
    target.path = /usr/lib
    INSTALLS += target
}
