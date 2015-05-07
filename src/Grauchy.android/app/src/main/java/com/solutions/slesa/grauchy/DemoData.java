package com.solutions.slesa.grauchy;

import persist.DbHelper;
import persist.SystemFlag;

public class DemoData {

    private DbHelper _dbHelper;

    public DemoData(DbHelper dbHelper) {
        _dbHelper = dbHelper;
    }

    public void createDemoData() {
        createZshKeys();
        createVimKeys();
        long rsIdx = _dbHelper.packageTable().addPackage("Resharper", "Visual Studio Extension");
        long vsIdx = _dbHelper.packageTable().addPackage("Visual Studio", "Visual Studio");
    }

    private void createZshKeys() {
        long zshIdx = _dbHelper.packageTable().addPackage("Zsh", "The glorious shell");

        long startLine = _dbHelper.hotkeyTable().addHotkey(zshIdx, "Ctrl+a", SystemFlag.SystemAll);
    }

    private void createVimKeys() {
        long vimIdx = _dbHelper.packageTable().addPackage("Vi", "The best editor");

    }
}
