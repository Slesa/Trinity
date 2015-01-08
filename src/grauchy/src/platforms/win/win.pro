TEMPLATE	= lib
TARGET		= grauchy.platform.win
CONFIG		+= qt_warn debug_and_release staticlib
INCLUDEPATH     += ../../common/
#CONFIG		-= embed_manifest_dll
QT		+= widgets

SOURCES		= win.cpp \
	platform_win.cpp

HEADERS		= \
	platform_win.h


if(!debug_and_release|build_pass):CONFIG(debug, debug|release) {
        DESTDIR = ../../../lib/
}

if(!debug_and_release|build_pass):CONFIG(release, debug|release) {
        DESTDIR = ../../../lib/
}
