#TEMPLATE		= lib
TARGET			= grauchy.specs
#CONFIG			+= qt_warn debug_and_release staticlib
QT				+= widgets testlib

MOC_DIR 		= .moc
INCLUDEPATH		+= ../grauchy

HEADERS 		= \
                commandlineparser.specs.h \
                singleapplication.specs.h \
                ../grauchy/commandlineparser.h \
                ../grauchy/singleapplication.h

SOURCES 		= main.cpp \
                commandlineparser.specs.cpp \
                singleapplication.specs.cpp \
                ../grauchy/commandlineparser.cpp \
                ../grauchy/singleapplication.cpp

DESTDIR 		= $${PWD}../../../bin/specs/
