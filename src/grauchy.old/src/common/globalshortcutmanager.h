/*
 * globalshortcutmanager.h - Class managing global shortcuts
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
#ifndef PLATFORM_BASE_HOTKEY
#define PLATFORM_BASE_HOTKEY

#include <QKeySequence>
#include <QMap>
#include <QObject>


class GlobalShortcutManager : public QObject
{
    class KeyTrigger;
public:
    ~GlobalShortcutManager();
    static GlobalShortcutManager* instance();
    static void connect(const QKeySequence& key, QObject* receiver, const char* slot);
    static void disconnect(const QKeySequence& key, QObject* receiver, const char* slot);
    static bool isConnected(const QKeySequence& key);


private:
    GlobalShortcutManager();
    static void clear();

private:
    static GlobalShortcutManager* _instance;
    QMap<QKeySequence, KeyTrigger*> _triggers;
};

#endif

#if 0

#ifndef GLOBALSHORTCUTMANAGER_H
#define GLOBALSHORTCUTMANAGER_H

#include <QObject>
#include <QKeySequence>


class QObject;
class KeyTrigger;

class GlobalShortcutManager : public QObject
{
public:
        GlobalShortcutManager();

};

#endif
#endif

