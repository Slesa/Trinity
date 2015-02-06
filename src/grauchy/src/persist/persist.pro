TEMPLATE 		= lib
TARGET 			= persist
CONFIG 			+= debug_and_release staticlib
win32:DEFINES	+= UNICODE _UNICODE

QT       		+= sql
QT       		-= gui


HEADERS 		+= persist.h \
    packagetable.h \
    tableinitializer.h \
    sqlexception.h

SOURCES 		+= persist.cpp \
    packagetable.cpp \
    tableinitializer.cpp \
    sqlexception.cpp

DESTDIR 		= $${PWD}../../../bin/lib/

unix {
    target.path = /usr/lib
    INSTALLS += target
}
