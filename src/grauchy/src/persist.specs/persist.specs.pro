#TEMPLATE		= lib
TARGET			= persist.specs
#CONFIG			+= qt_warn debug_and_release staticlib
QT				+= sql widgets testlib

MOC_DIR 		= .moc
INCLUDEPATH		+= ../

HEADERS 		= \
                persist.specs.h \
                ../persist/persist.h

SOURCES 		= main.cpp \
                persist.specs.cpp \
                ../persist/persist.cpp

LIBS			+= \
                -L$${PWD}/../../bin/lib \
                -lpersist \
                -ldata

DESTDIR 		= $${PWD}/../../../bin/specs/
