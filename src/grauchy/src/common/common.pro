TEMPLATE	= lib
TARGET		= grauchy.common
CONFIG		+= qt_warn debug_and_release staticlib
QT		+= widgets

HEADERS = \
        globalshortcutmanager.h \
        platform_base.h

SOURCES = \
        globalshortcutmanager.cpp \
        platform_base.cpp


if(!debug_and_release|build_pass):CONFIG(debug, debug|release) {
        DESTDIR = ../../lib/
}

if(!debug_and_release|build_pass):CONFIG(release, debug|release) {
        DESTDIR = ../../lib/
}

