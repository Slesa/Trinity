/*
 * globalshortcutmanager_mac.cpp - Mac OS X implementation of global shortcuts
 * Copyright (C) 2003-2007  Eric Smith, Michail Pishchagin
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
#include "mac_keytriggermanager.h"
#include "mac_keytrigger.h"
#include <QCoreApplication>
#include <Carbon/Carbon.h>
//#include <CarbonCore/Script.h>

MacKeyTriggerManager* MacKeyTriggerManager::_instance = NULL;
EventHandlerUPP MacKeyTriggerManager::_hot_key_function = NULL;
MacKeyTriggerManager::Ascii2KeyCodeTable MacKeyTriggerManager::_key_codes;

MacKeyTriggerManager* MacKeyTriggerManager::instance()
{
    if(!_instance)
        _instance = new MacKeyTriggerManager();
    return _instance;
}

void MacKeyTriggerManager::addTrigger(MacKeyTrigger* trigger)
{
    _triggers << trigger;
}

void MacKeyTriggerManager::removeTrigger(MacKeyTrigger* trigger)
{
    _triggers.removeAll(trigger);
}

MacKeyTriggerManager::MacKeyTriggerManager()
    : QObject(QCoreApplication::instance())
{
    initAscii2KeyCodeTable(&_key_codes);
    _hot_key_function = NewEventHandlerUPP(hotKeyHandler);
    EventTypeSpec type;
    type.eventClass = kEventClassKeyboard;
    type.eventKind = kEventHotKeyPressed;
    InstallApplicationEventHandler(_hot_key_function, 1, &type, this, NULL);
}

/**
 * Callback function invoked when the user hits a hot-key.
 */
pascal OSStatus MacKeyTriggerManager::hotKeyHandler(EventHandlerCallRef /*nextHandler*/, EventRef theEvent, void* userData)
{
    EventHotKeyID hkID;
    GetEventParameter(theEvent, kEventParamDirectObject, typeEventHotKeyID, NULL, sizeof(EventHotKeyID), NULL, &hkID);
    static_cast<MacKeyTriggerManager*>(userData)->activated(hkID.id);
    return noErr;
}

void MacKeyTriggerManager::activated(int id)
{
    foreach(MacKeyTrigger* trigger, _triggers) {
        if (trigger->isAccepted(id)) {
            trigger->activate();
            break;
        }
    }
}

/**
 * initAscii2KeyCodeTable initializes the ascii to key code
 * look up table using the currently active KCHR resource. This
 * routine calls GetResource so it cannot be called at interrupt time.
 */
OSStatus MacKeyTriggerManager::initAscii2KeyCodeTable(Ascii2KeyCodeTable* ttable)
{
    unsigned char* theCurrentKCHR, *ithKeyTable;
    short count, i, j, resID;
    Handle theKCHRRsrc;
    ResType rType;

    // set up our table to all minus ones
    for (i = 0; i < 256; i++)
        ttable->transtable[i] = -1;

    // find the current kchr resource ID
// @@@    ttable->kchrID = (short)GetScriptVariable(smCurrentScript, smScriptKeys);

    // get the current KCHR resource
    theKCHRRsrc = GetResource('KCHR', ttable->kchrID);
    if (theKCHRRsrc == NULL)
        return resNotFound;
    GetResInfo(theKCHRRsrc, &resID, &rType, ttable->KCHRname);

    // dereference the resource
    theCurrentKCHR = (unsigned char *)(*theKCHRRsrc);

    // get the count from the resource
    count = *(short*)(theCurrentKCHR + kTableCountOffset);

    // build inverse table by merging all key tables
    for (i = 0; i < count; i++) {
        ithKeyTable = theCurrentKCHR + kFirstTableOffset + (i * kTableSize);
        for (j = 0; j < kTableSize; j++) {
            if (ttable->transtable[ ithKeyTable[j] ] == -1)
                ttable->transtable[ ithKeyTable[j] ] = j;
        }
    }

    return noErr;
}

/**
 * validateAscii2KeyCodeTable verifies that the ascii to key code
 * lookup table is synchronized with the current KCHR resource. If
 * it is not synchronized, then the table is re-built. This routine calls
 * GetResource so it cannot be called at interrupt time.
 *
 * Should probably call this at some point, in case the user has switched keyboard
 * layouts while we were running.
 */
OSStatus MacKeyTriggerManager::validateAscii2KeyCodeTable(Ascii2KeyCodeTable* ttable, Boolean* wasChanged)
{
/* @@@
    short theID;
    theID = (short) GetScriptVariable(smCurrentScript, smScriptKeys);
    if (theID != ttable->kchrID) {
        *wasChanged = true;
        return initAscii2KeyCodeTable(ttable);
    }
    else {
        *wasChanged = false;
        return noErr;
} */
*wasChanged = false;
return noErr;
}

/**
 * asciiToKeyCode looks up the ascii character in the key
 * code look up table and returns the virtual key code for that
 * letter. If there is no virtual key code for that letter, then
 * the value -1 will be returned.
 */
short MacKeyTriggerManager::asciiToKeyCode(Ascii2KeyCodeTable* ttable, short asciiCode)
{
    if (asciiCode >= 0 && asciiCode <= 255)
        return ttable->transtable[asciiCode];
    else return false;
}

/**
 * Not used.
static char MacKeyTriggerManager::keyCodeToAscii(short virtualKeyCode)
{
    unsigned long state;
    long keyTrans;
    char charCode;
    Ptr kchr;
    state = 0;
    kchr = (Ptr)GetScriptVariable(smCurrentScript, smKCHRCache);
    keyTrans = KeyTranslate(kchr, virtualKeyCode, &state);
    charCode = keyTrans;
    if (!charCode)
        charCode = (keyTrans >> 16);
    return charCode;
}
 */

bool MacKeyTriggerManager::convertKeySequence(const QKeySequence& ks, quint32* _key, quint32* _mod)
{
    int code = ks[0];

    quint32 mod = 0;
    if (code & Qt::META)
        mod |= controlKey;
    if (code & Qt::SHIFT)
        mod |= shiftKey;
    if (code & Qt::CTRL)
        mod |= cmdKey;
    if (code & Qt::ALT)
        mod |= optionKey;

    code &= ~Qt::KeyboardModifierMask;
    quint32 key = 0;
    for (int n = 0; qt_keymap[n].qt_key != Qt::Key_unknown; ++n) {
        if (qt_keymap[n].qt_key == code) {
            key = qt_keymap[n].mac_key;
            break;
        }
    }
    if (key == 0) {
        key = asciiToKeyCode(&_key_codes, code & 0xffff);
    }

    if (_mod)
        *_mod = mod;
    if (_key)
        *_key = key;

    return true;
}
