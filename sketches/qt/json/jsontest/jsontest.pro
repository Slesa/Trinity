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


SOURCES += tst_jsontest.cpp \
    article.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

HEADERS += \
    article.h
