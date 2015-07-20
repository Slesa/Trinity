TEMPLATE		= lib
TARGET			= grauchy.common
CONFIG			+= qt_warn debug_and_release staticlib
QT				+= widgets
win32:QT		+= winextras
linux:QT    	+= x11extras
mac:QT			+= macextras

HEADERS 		= \
                platform_base.h \
                globalshortcutmanager.h \
                globalshortcuttrigger.h \
    globals.h
SOURCES 		= \
                platform_base.cpp \
                globalshortcutmanager.cpp \
    globals.cpp

linux:HEADERS	+= \
				x11_platform.h \
				x11_keytrigger.h
linux:SOURCES	+= x11.cpp \
                x11_platform.cpp \
                x11_keytrigger.cpp

win32:HEADERS	+= \
                win_platform.h
win32:SOURCES	+= win.cpp \
                win_platform.cpp \
                win_keytrigger.cpp

mac:HEADERS		+= \
                mac_platform.h \
                mac_keytrigger.h \
                mac_keytriggermanager.h
mac:SOURCES		+= mac.cpp \
                mac_platform.cpp \
                mac_keytrigger.cpp \
                mac_keytriggermanager.cpp

DESTDIR 		= $${PWD}../../../bin/lib/

#if(!debug_and_release|build_pass):CONFIG(debug, debug|release) {
#        DESTDIR = ../../lib/
#}

#if(!debug_and_release|build_pass):CONFIG(release, debug|release) {
#        DESTDIR = ../../lib/
#}

