TEMPLATE		= lib
TARGET			= grauchy.platform.unix
CONFIG			+= qt_warn debug_and_release staticlib
INCLUDEPATH    	+= ../../common/
#CONFIG			-= embed_manifest_dll
QT				+= widgets
win32:QT		+= winextras
linux:QT    	+= x11extras

SOURCES			= unix.cpp \
                platform_unix.cpp \
                x11_keytrigger.cpp

# platform_x11_hotkey.cpp platform_base_hotkey.cpp platform_unix.cpp platform_unix_util.cpp

HEADERS			= \
                platform_unix.h \
                x11_keytrigger.h

# platform_base.h platform_unix.h platform_base_hotkey.h platform_base_hottrigger.h  platform_unix_util.h platform_x11_hotkey.h

# LIBS			+= grauchy.common
# LIBS += -lX11 -lXext -lXrender


#unix {
# PREFIX = /usr
# DEFINES += SKINS_PATH=\\\"$$PREFIX/share/launchy/skins/\\\" \
#           PLUGINS_PATH=\\\"$$PREFIX/lib/launchy/plugins/\\\" \
#           PLATFORMS_PATH=\\\"$$PREFIX/lib/launchy/\\\"
# target.path = $$PREFIX/lib/launchy/
# INSTALLS += target
#}

DESTDIR			= ../../../lib/

#if(!debug_and_release|build_pass):CONFIG(debug, debug|release) {
#        DESTDIR = ../../../lib/
#}

#if(!debug_and_release|build_pass):CONFIG(release, debug|release) {
#        DESTDIR = ../../../lib/
#}
