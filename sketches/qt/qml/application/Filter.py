# -*- coding: utf-8 -*-

try:
    from PySide import QtWidgets
except:
    from PyQt5 import QtWidgets


class Filter:
    def __init__(self, title):
        self.title = title

    title = property(fget=_title)
