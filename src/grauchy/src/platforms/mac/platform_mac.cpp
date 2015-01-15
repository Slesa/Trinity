#include "platform_mac.h"
#include "globalshortcutmanager.h"
#include <QDebug>

PlatformMac::PlatformMac(int& argc, char** argv) 
    : PlatformBase(argc, argv)
{
} 

bool PlatformMac::setHotkey(const QKeySequence & key, QObject* receiver, const char* slot)
{
    GlobalShortcutManager::disconnect(oldKey, receiver, slot);
    GlobalShortcutManager::connect(key, receiver, slot);
    oldKey = key;
    qDebug() << key << GlobalShortcutManager::isConnected(key);
    return GlobalShortcutManager::isConnected(key);
}
