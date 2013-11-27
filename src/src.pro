QT       += core gui-private

TARGET = emukeysplugin

PLUGIN_TYPE = generic
PLUGIN_CLASS_NAME = EmuKeysPlugin
load(qt_plugin)

DESTDIR = ../build/generic

SOURCES += emukeysplugin.cpp \
    emukeyshandler.cpp

HEADERS += emukeysplugin.h \
    emukeyshandler.h
OTHER_FILES += emukeys.json

*-g++*:QMAKE_CXXFLAGS += -std=c++0x
