#-------------------------------------------------
#
# Project created by QtCreator 2014-12-17T22:41:29
#
#-------------------------------------------------

QT       += testlib

QT       -= gui

TARGET = tst_jsontest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += \
    article.cpp \
    articletest.cpp \
    family.cpp \
    familytest.cpp \
    jsonfile.cpp \
    jsontest.cpp \
    main.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

HEADERS += \
    article.h \
    articletest.h \
    family.h \
    familytest.h \
    jsonfile.h \
    jsontest.h
