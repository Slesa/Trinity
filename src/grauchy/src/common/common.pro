TEMPLATE		= lib
TARGET			= grauchy.common
CONFIG			+= qt_warn debug_and_release staticlib
QT				+= widgets

HEADERS 		= \
                keytrigger.h \
                platform_base.h \
                globalshortcutmanager.h

SOURCES 		= \
                platform_base.cpp \
                globalshortcutmanager.cpp

DESTDIR 		= ../../lib/

#if(!debug_and_release|build_pass):CONFIG(debug, debug|release) {
#        DESTDIR = ../../lib/
#}

#if(!debug_and_release|build_pass):CONFIG(release, debug|release) {
#        DESTDIR = ../../lib/
#}

