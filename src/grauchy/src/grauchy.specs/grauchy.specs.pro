#TEMPLATE		= lib
TARGET			= grauchy.specs
#CONFIG			+= qt_warn debug_and_release staticlib
QT				+= widgets testlib

MOC_DIR 		= .moc
INCLUDEPATH		+= ../grauchy

HEADERS 		= \
                ../grauchy/commandlineparser.h

SOURCES 		= \
                commandlineparser.specs.cpp \
                ../grauchy/commandlineparser.cpp

DESTDIR 		= ../../specs/
