#include "mac_platform.h"
#include "globalshortcutmanager.h"
#include <QDebug>

MacPlatform::MacPlatform(int& argc, char** argv)
    : PlatformBase(argc, argv)
{
} 

bool MacPlatform::setHotkey(const QKeySequence & key, QObject* receiver, const char* slot)
{
    GlobalShortcutManager::disconnect(oldKey, receiver, slot);
    GlobalShortcutManager::connect(key, receiver, slot);
    oldKey = key;
    qDebug() << key << GlobalShortcutManager::isConnected(key);
    return GlobalShortcutManager::isConnected(key);
}
