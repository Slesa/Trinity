#!/usr/bin/python3
# -*- coding: utf-8 -*-
from PyQt5.QtWidgets import QApplication
from PyQt5.QtQml import QQmlApplicationEngine, qmlRegisterType
import sys, os


import gui

if __name__=="__main__":
    import sys

    app = QApplication(sys.argv)

    engine = QQmlApplicationEngine()

    mainview = gui.MainView (engine)
    if not mainview.show():
        sys.exit(-1)

    sys.exit(app.exec_())
