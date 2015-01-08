#ifndef PLATFORM_UNIX
#define PLATFORM_UNIX

#include "platform_base.h"

class PlatformUnix :  public PlatformBase
{
    Q_OBJECT

public:
    PlatformUnix(int & argc, char** argv);

};

#endif


#if 0
#pragma once

#include "platform_unix_util.h"
#include "platform_base_hotkey.h"
#include "platform_base_hottrigger.h"

// @@@ #include <QX11Info>

#include <X11/X.h>
#include <X11/Xlib.h>


class PlatformUnix :  public PlatformBase
{
    Q_OBJECT

    bool x11EventFilter ( XEvent * event ) {
        if (event->type == KeyPress) {
            emit xkeyPressed(event);
        }
        return false;
    }

    QKeySequence oldKey;
 public:
    ~PlatformUnix();
    
    void setPreferredIconSize(int size) { size = size; return; }

    //virtual shared_ptr<QApplication> init(int & argc, char** argv);
    // Mandatory functions
    // Mandatory functions
    bool setHotkey(const QKeySequence& key, QObject* receiver, const char* slot)
    {

	GlobalShortcutManager::disconnect(oldKey, receiver, slot);
	GlobalShortcutManager::connect(key, receiver, slot);
	oldKey = key;
        qDebug() << key << GlobalShortcutManager::isConnected(key);
	return GlobalShortcutManager::isConnected(key);
    }
    

    QKeySequence getHotkey() const
    {
        return oldKey;
    }

    QString GetSettingsDirectory() { 
	return "";
    }

    
    QList<Directory> getDefaultCatalogDirectories();
    
    
    void AddToNotificationArea() {};
    void RemoveFromNotificationArea() {};
    
    bool isAlreadyRunning() const {
	return false;
    }


    virtual QHash<QString, QList<QString> > getDirectories();
	virtual QString expandEnvironmentVars(QString txt);

    bool supportsAlphaBorder() const;
    /*
    QIcon icon(const QFileInfo& info) {
    	shared_ptr<UnixIconProvider> u(dynamic_pointer_cast<UnixIconProvider>(icons));
  	  	return u->getIcon(info);
//		return ((UnixIconProvider*) icons.get())->getIcon(info); 
    }
    */

    virtual void alterItem(CatItem*);
    signals:
    void xkeyPressed(XEvent*);

};
#endif
