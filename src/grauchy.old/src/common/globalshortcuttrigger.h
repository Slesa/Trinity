/*
 * globalshortcuttrigger.h - Helper class activating global shortcut
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
#ifndef KEYTRIGGER_H
#define KEYTRIGGER_H

#include "globalshortcutmanager.h"

#ifdef Q_OS_MAC
#include <memory>
#endif
#ifdef Q_OS_WIN32
#include <memory>
#endif
#ifdef Q_OS_LINUX
#include <auto_ptr.h>
#endif

class GlobalShortcutManager::KeyTrigger : public QObject
{
    Q_OBJECT
public:
    /**
     * Is there any slot connected to this hotkey?
     */
    bool isUsed() const
    {
        return QObject::receivers(SIGNAL(activated())) > 0;
    }

signals:
    void activated();

private:
    /**
     * Registers the \a key.
     */
    KeyTrigger(const QKeySequence& key);
    /**
     * Unregisters the key.
     */
    ~KeyTrigger();

    friend class GlobalShortcutManager;
    bool isConnected();

    /**
      * Platform-specific helper
      */
    class Impl;
    std::auto_ptr<Impl> d;
};

#endif // KEYTRIGGER_H
