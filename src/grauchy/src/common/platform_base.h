/* Copyright (C) 2007-2009  Josh Karlin, Simon Capewell */
#ifndef PLATFORM_BASE_H
#define PLATFORM_BASE_H

#include <QApplication>
#include <QKeySequence>

class QFileIconProvider;

// Platform dependent creation of qApp
QApplication* createApplication(int& argc, char** argv);

class PlatformBase : public QApplication
{
public:
    PlatformBase(int& argc, char** argv);
    virtual ~PlatformBase();

protected:
    QFileIconProvider* _icons;
    QKeySequence hotkey;
};

#endif

#if 0




#include <QtGui> // OSX needs this
#include <QApplication>
#include <QFileIconProvider>
#include "Directory.h"
#include "catalog.h"
#include "globals.h"


class PlatformBase : public QApplication
{
public:
	PlatformBase(int& argc, char** argv) : 
	  QApplication(argc, argv)
	{
		platform = this;
	}


	QIcon icon(const QFileInfo& info) { return icons->icon(info); }
	QIcon icon(QFileIconProvider::IconType type) { return icons->icon(type); }
	virtual void setPreferredIconSize(int size) = 0;

	virtual QList<Directory> getDefaultCatalogDirectories() = 0;
	virtual bool isAlreadyRunning() const = 0;
	virtual void sendInstanceCommand(int command) { Q_UNUSED(command); }

	// Set hotkey
	virtual QKeySequence getHotkey() const = 0;
	virtual bool setHotkey(const QKeySequence& key, QObject* receiver, const char* slot) = 0;

	// Need to alter an indexed item?  e.g. .desktop files
	virtual void alterItem(CatItem*) { }
	virtual QHash<QString, QList<QString> > getDirectories() = 0;
	virtual QString expandEnvironmentVars(QString txt) = 0;

	virtual bool supportsAlphaBorder() const { return false; }
	virtual bool getComputers(QStringList& computers) const { Q_UNUSED(computers); return false; }


};



#endif
