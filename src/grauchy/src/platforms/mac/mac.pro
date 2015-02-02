TEMPLATE		= lib
TARGET			= grauchy.platform.mac
CONFIG			+= qt_warn debug_and_release staticlib
INCLUDEPATH     += ../../common/
#CONFIG			-= embed_manifest_dll
QT				+= widgets
mac:QT			+= macextras

SOURCES			= mac.cpp \
                mac_keytrigger.cpp \
                platform_mac.cpp

HEADERS			= \
				mac_keytrigger.h \
                platform_mac.h
                

DESTDIR			= ../../../lib/
DLLDESTDIR		= ../../../bin/

#if(!debug_and_release|build_pass):CONFIG(debug, debug|release) {
#        DESTDIR = ../../../lib/
#}

#if(!debug_and_release|build_pass):CONFIG(release, debug|release) {
#        DESTDIR = ../../../lib/
#}
