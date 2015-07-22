# -*- coding: utf-8 -*-

from PyQt5.QtCore import QDir, QObject, \
    pyqtSlot, pyqtProperty, pyqtSignal


class MainView(QObject):

	def __init__(self, engine):
		super(MainView, self).__init__()
		self.engine = engine


	def show(self):

		qmlFile = 'qml/main.qml'
		self.engine.load(qmlFile)

		if not self.engine.rootObjects():
			print ('Error: could not initialize')
			return False

		win = self.engine.rootObjects()[0]
		win.show()
		return True
