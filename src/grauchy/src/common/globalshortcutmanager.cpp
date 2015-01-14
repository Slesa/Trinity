/*
 * globalshortcutmanager.cpp - Class managing global shortcuts
 * Copyright (C) 2006  Maciej Niedzielski
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 */
#include "globalshortcutmanager.h"
#include "keytrigger.h"
#include <QCoreApplication>
#include <QMutex>

GlobalShortcutManager* GlobalShortcutManager::_instance;

GlobalShortcutManager::~GlobalShortcutManager()
{
    clear();
}

GlobalShortcutManager* GlobalShortcutManager::instance()
{
    static QMutex mutex;
    if (!_instance)
    {
        mutex.lock();
        _instance = new GlobalShortcutManager();
        mutex.unlock();
    }
    return _instance;
}

void GlobalShortcutManager::connect(const QKeySequence& key, QObject* receiver, const char* slot)
{
    KeyTrigger* t = instance()->_triggers[key];
    if( !t )
    {
        t = new KeyTrigger(key);
        instance()->_triggers.insert(key, t);
    }

    QObject::connect(t, SIGNAL(activated()), receiver, slot);
}

/**
 * \brief Connects a key sequence with a slot.
 * \param key, global shortcut to be connected
 * \param receiver, object which should receive the notification
 * \param slot, the SLOT() of the \a receiver which should be triggerd if the \a key is activated
 */
bool GlobalShortcutManager::isConnected(const QKeySequence& key)
{
    KeyTrigger* t = instance()->_triggers[key];
    if (!t)
        return false;
    return t->isConnected();
}

/**
 * \brief Disonnects a key sequence from a slot.
 * \param key, global shortcut to be disconnected
 * \param receiver, object which \a slot is about to be disconnected
 * \param slot, the SLOT() of the \a receiver which should no longer be triggerd if the \a key is activated
 */
void GlobalShortcutManager::disconnect(const QKeySequence& key, QObject* receiver, const char* slot)
{
    KeyTrigger* t = instance()->_triggers[key];
    if( !t )  return;

    QObject::disconnect(t, SIGNAL(activated()), receiver, slot);
    delete instance()->_triggers.take(key);
}

void GlobalShortcutManager::clear()
{
    foreach (KeyTrigger* t, instance()->_triggers)
        delete t;
    instance()->_triggers.clear();
}

GlobalShortcutManager::GlobalShortcutManager()
: QObject(QCoreApplication::instance())
{
}

#if 0


#include "platform_base_hotkey.h"
#include "platform_base_hottrigger.h"
#include <QCoreApplication>





#endif

