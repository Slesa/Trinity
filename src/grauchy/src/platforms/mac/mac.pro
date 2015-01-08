TEMPLATE		= lib
TARGET			= grauchy.platform.mac
CONFIG			+= qt_warn debug_and_release staticlib
INCLUDEPATH     += ../../common/
#CONFIG		-= embed_manifest_dll
QT				+= widgets

SOURCES			= mac.cpp \
                platform_mac.cpp

HEADERS			= \
                platform_mac.h

DESTDIR			= ../../../lib/

#if(!debug_and_release|build_pass):CONFIG(debug, debug|release) {
#        DESTDIR = ../../../lib/
#}

#if(!debug_and_release|build_pass):CONFIG(release, debug|release) {
#        DESTDIR = ../../../lib/
#}
