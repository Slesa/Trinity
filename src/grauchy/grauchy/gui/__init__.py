# -*- coding: utf-8 -*-
import os, sys

wcd = os.getcwd()
sys.path.append(wcd)
gui = os.path.join(wcd, 'gui')
sys.path.append(gui)

from mainview import MainView
