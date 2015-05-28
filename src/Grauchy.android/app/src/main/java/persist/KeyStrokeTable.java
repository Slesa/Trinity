package persist;

import android.database.sqlite.SQLiteDatabase;

public class KeyStrokeTable extends TableBase {

    private static final String TABLE_NAME = "keystrokes";
    private static final String FIELD_HOTKEY = "hotkey";
    private static final String FIELD_SYSTEM = "system";
    private static final String FIELD_SEQ = "sequence";

    private DbHelper _dbHelper;

    public KeyStrokeTable(DbHelper dbHelper) {
        _dbHelper = dbHelper;
    }

    public void createTable(SQLiteDatabase db) {
        String buffer = startCreateTable(TABLE_NAME);
        buffer = addPrimaryKey(buffer);
        buffer = addCreateColumn(buffer, TYPE_INT, FIELD_HOTKEY);
        buffer = addCreateColumn(buffer, TYPE_INT, FIELD_SYSTEM);
        buffer = addCreateColumn(buffer, TYPE_TEXT, FIELD_SEQ, true);
        db.execSQL(buffer);
    }

}
