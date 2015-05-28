#include "demodata.h"
#include "persist/packagetable.h"
#include "persist/hotkeytable.h"
#include "persist/keystroketable.h"

DemoData::DemoData()
{
}


void DemoData::createDemoData()
{
    PackageTable packageTable;
    QSqlQuery query = packageTable.prepareInsertion();

    createZshKeys(packageTable, query);
    createVimKeys(packageTable, query);

    int rsIdx = packageTable.addPackage(query, "Resharper", "Visual Studio Extension");
    int vsIdx = packageTable.addPackage(query, "Visual Studio", "Visual Studio");
}

void DemoData::createZshKeys(PackageTable& packageTable, QSqlQuery& queryPackage)
{
    int zshIdx = packageTable.addPackage(queryPackage, "Zsh", "The glorious shell");

    HotkeyTable hotkeyTable;
    QSqlQuery queryHotkey = hotkeyTable.prepareInsertion();

    KeyStrokeTable keyStrokeTable;
    QSqlQuery queryStroke = keyStrokeTable.prepareInsertion();

    int zshStartLine = hotkeyTable.addHotkey(queryHotkey, zshIdx, "Goto start of line", "");
    keyStrokeTable.addKeyStroke(queryStroke, zshStartLine, "Ctrl+a", SystemAll);

    int zshEndLine = hotkeyTable.addHotkey(queryHotkey, zshIdx, "Goto end of line", "");
    keyStrokeTable.addKeyStroke(queryStroke, zshEndLine, "Ctrl+e", SystemAll);

    int zshStartNextWord = hotkeyTable.addHotkey(queryHotkey, zshIdx, "Goto start of next word", "");
    keyStrokeTable.addKeyStroke(queryStroke, zshStartNextWord, "Esc+f", SystemAll);

    int zshEndPrevWord = hotkeyTable.addHotkey(queryHotkey, zshIdx, "Goto end of previous word", "");
    keyStrokeTable.addKeyStroke(queryStroke, zshEndPrevWord, "Esc+e", SystemAll);

    int zshMatchBrace = hotkeyTable.addHotkey(queryHotkey, zshIdx, "Goto matching bracket", "");
    keyStrokeTable.addKeyStroke(queryStroke, zshMatchBrace, "Ctrl+x,Ctrl+b", SystemAll);

    int zshStartCurrWord = hotkeyTable.addHotkey(queryHotkey, zshIdx, "Remove from cursor postion to start of current word", "");
    keyStrokeTable.addKeyStroke(queryStroke, zshStartCurrWord, "Ctrl+w", SystemAll);

    int zshEndCurrWord = hotkeyTable.addHotkey(queryHotkey, zshIdx, "Remove from cursor position to end of current word", "");
    keyStrokeTable.addKeyStroke(queryStroke, zshEndCurrWord, "Esc+d", SystemAll);

    int zshEndOfLine = hotkeyTable.addHotkey(queryHotkey, zshIdx, "Remove from cursor position to end of line", "");
    keyStrokeTable.addKeyStroke(queryStroke, zshEndOfLine, "Ctrl+k", SystemAll);

    int zshWholeLine = hotkeyTable.addHotkey(queryHotkey, zshIdx, "Remove the whole line", "");
    keyStrokeTable.addKeyStroke(queryStroke, zshWholeLine, "Ctrl+u", SystemAll);
}

void DemoData::createVimKeys(PackageTable& packageTable, QSqlQuery& queryPackage)
{
    int viIdx = packageTable.addPackage(queryPackage, "Vi", "The best editor");

    HotkeyTable hotkeyTable;
    QSqlQuery queryHotkey = hotkeyTable.prepareInsertion();

    KeyStrokeTable keyStrokeTable;
    QSqlQuery queryStroke = keyStrokeTable.prepareInsertion();

    int viStartLine = hotkeyTable.addHotkey(queryHotkey, viIdx, "Goto start of line", "");
    keyStrokeTable.addKeyStroke(queryStroke, viStartLine, "^", SystemAll);

    int viEndLine = hotkeyTable.addHotkey(queryHotkey, viIdx, "Goto end of line", "");
    keyStrokeTable.addKeyStroke(queryStroke, viEndLine, "$", SystemAll);

    int viStartDoc = hotkeyTable.addHotkey(queryHotkey, viIdx, "Goto start of document", "");
    keyStrokeTable.addKeyStroke(queryStroke, viStartDoc, "gg", SystemAll);

    int viEndDoc = hotkeyTable.addHotkey(queryHotkey, viIdx, "Goto end of document", "");
    keyStrokeTable.addKeyStroke(queryStroke, viEndDoc, "G", SystemAll);
}
