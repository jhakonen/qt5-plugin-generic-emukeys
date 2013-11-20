#-------------------------------------------------
#
# Project created by QtCreator 2013-11-20T16:06:18
#
#-------------------------------------------------

QT       += core

TARGET = qt5-plugin-generic-emukeys
TEMPLATE = lib
CONFIG += plugin

DESTDIR = $$[QT_INSTALL_PLUGINS]/codecs

SOURCES += emukeysplugin.cpp \
    emukeyshandler.cpp

HEADERS += emukeysplugin.h \
    emukeyshandler.h
OTHER_FILES += emukeys.json

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}
