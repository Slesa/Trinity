package persist;

import android.content.ContentValues;
import android.database.sqlite.SQLiteDatabase;

public class HotkeyTable extends TableBase {

    private static final String TABLE_NAME = "hotkeys";
    private static final String FIELD_PACKAGE = "package";
    private static final String FIELD_DESCR = "descr";
    private static final String FIELD_HINT = "hint";

    private DbHelper _dbHelper;

    public HotkeyTable(DbHelper dbHelper) {
        _dbHelper = dbHelper;
    }

    public void createTable(SQLiteDatabase db) {
        String buffer = startCreateTable(TABLE_NAME);
        buffer = addPrimaryKey(buffer);
        buffer = addCreateColumn(buffer, TYPE_INT, FIELD_PACKAGE);
        buffer = addCreateColumn(buffer, TYPE_TEXT, FIELD_DESCR);
        buffer = addCreateColumn(buffer, TYPE_TEXT, FIELD_HINT, true);
        db.execSQL(buffer);
    }

    public long addHotkey(long pack, String descr, SystemFlag systems) {
        SQLiteDatabase db = _dbHelper.getWritableDatabase();

        ContentValues values = new ContentValues();
        values.put(FIELD_PACKAGE, pack);
        values.put(FIELD_DESCR, descr);

        long id = db.insert(TABLE_NAME, null, values);
        return id;
    }
}
