TEMPLATE = subdirs

win32:SUBDIRS = win
unix:!macx:SUBDIRS = unix
macx:SUBDIRS = mac
