TEMPLATE		= lib
TARGET			= grauchy.common
CONFIG			+= qt_warn debug_and_release staticlib
QT				+= widgets
win32:QT		+= winextras
linux:QT    	+= x11extras
mac:QT			+= macextras

HEADERS 		= \
                keytrigger.h \
                platform_base.h \
                globalshortcutmanager.h
linux:HEADERS	+= \
				x11_platform.h \
				x11_keytrigger.h
win32:HEADERS	+= \
                win_platform.h
mac:HEADERS		+= \
                mac_platform.h \
                mac_keytrigger.h

SOURCES 		= \
                platform_base.cpp \
                globalshortcutmanager.cpp
linux:SOURCES	+= x11.cpp \
				x11_platform.cpp \
				x11_keytrigger.cpp
win32:SOURCES	+= win.cpp \
                win_platform.cpp \
                win_keytrigger.cpp
mac:SOURCES		+= mac.cpp \
                mac_platform.cpp \
                mac_keytrigger.cpp

DESTDIR 		= ../../lib/

#if(!debug_and_release|build_pass):CONFIG(debug, debug|release) {
#        DESTDIR = ../../lib/
#}

#if(!debug_and_release|build_pass):CONFIG(release, debug|release) {
#        DESTDIR = ../../lib/
#}

