QT += qml quick

# If your application uses the Qt Mobility libraries, uncomment the following
# lines and add the respective components to the MOBILITY variable.
# CONFIG += mobility
# MOBILITY +=

# The .cpp file which was generated for your project. Feel free to hack it.
SOURCES += main.cpp \
    keysource.cpp

# Installation path
# target.path =

DESTDIR = ../../build

HEADERS += \
    keysource.h

RESOURCES += \
    resources.qrc

OTHER_FILES += \
    main.qml \
    ButtonIndicator.qml
