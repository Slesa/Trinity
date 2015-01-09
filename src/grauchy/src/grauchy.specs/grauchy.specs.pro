#TEMPLATE		= lib
TARGET			= grauchy.specs
#CONFIG			+= qt_warn debug_and_release staticlib
QT				+= widgets testlib

MOC_DIR 		= .moc
INCLUDEPATH		+= ../grauchy

HEADERS 		= \
                commandlineparser.specs.h \
                ../grauchy/commandlineparser.h

SOURCES 		= main.cpp \
                commandlineparser.specs.cpp \
                ../grauchy/commandlineparser.cpp

DESTDIR 		= ../../specs/
