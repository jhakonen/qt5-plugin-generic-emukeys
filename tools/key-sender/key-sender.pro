QT += qml quick

# If your application uses the Qt Mobility libraries, uncomment the following
# lines and add the respective components to the MOBILITY variable.
# CONFIG += mobility
# MOBILITY +=

SOURCES += \
    main.cpp \
    keysender.cpp

# Installation path
# target.path =

DESTDIR = ../../build

RESOURCES += \
    resources.qrc

OTHER_FILES += \
    main.qml \
    Button.qml

HEADERS += \
    keysender.h

*-g++*:QMAKE_CXXFLAGS += -std=c++0x
