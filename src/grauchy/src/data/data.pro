TEMPLATE		= lib
TARGET			= data
CONFIG			+= qt_warn debug_and_release staticlib
win32:DEFINES	+= UNICODE _UNICODE

HEADERS 		= \
                package.h \
                hotkey.h \
    modifiers.h \
    systems.h \
    keystroke.h

SOURCES 		= \
                package.cpp \
                hotkey.cpp \
    keystroke.cpp

DESTDIR 		= $${PWD}../../../bin/lib/


