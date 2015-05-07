package persist;

import android.content.Context;
import android.database.sqlite.SQLiteDatabase;
import android.database.sqlite.SQLiteOpenHelper;

public class DbHelper extends SQLiteOpenHelper{

    public static final int DATABASE_VERSION = 1;
    public static final String DATABASE_NAME = "grauchy.db";

    public DbHelper(Context context) {
        super(context, DATABASE_NAME, null, DATABASE_VERSION);
    }

    private PackageTable _packageTable;
    public PackageTable packageTable() {
        if(_packageTable==null)
            _packageTable = new PackageTable(this);
        return _packageTable;
    }

    private HotkeyTable _hotkeyTable;
    public HotkeyTable hotkeyTable() {
        if(_hotkeyTable==null)
            _hotkeyTable = new HotkeyTable(this);
        return _hotkeyTable;
    }

    private KeyStrokeTable _keyStrokeTable;
    public KeyStrokeTable keyStrokeTable() {
        if(_keyStrokeTable==null)
            _keyStrokeTable = new KeyStrokeTable();
        return _keyStrokeTable;
    }

    @Override
    public void onCreate(SQLiteDatabase db) {
        packageTable().createTable();
        hotkeyTable().createTable();
        keyStrokeTable().createTable(db);
    }

    @Override
    public void onUpgrade(SQLiteDatabase db, int oldVersion, int newVersion) {

    }
}
