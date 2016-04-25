TEMPLATE = app

QT += qml quick
CONFIG += c++11

SOURCES += main.cpp \
    model/room.cpp \
    model/floor.cpp \
    model/building.cpp \
    buildingcontroller.cpp \
    floorsmodel.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    model/room.h \
    model/floor.h \
    model/building.h \
    buildingcontroller.h \
    floorsmodel.h

