package persist;

import android.content.ContentValues;
import android.database.sqlite.SQLiteDatabase;

public class PackageTable extends TableBase {

    private static final String TABLE_NAME = "packages";
    private static final String FIELD_NAME = "name";
    private static final String FIELD_DESCR = "descr";

    private DbHelper _dbHelper;

    public PackageTable(DbHelper dbHelper) {
        _dbHelper = dbHelper;
    }

    public void createTable() {
        String buffer = startCreateTable(TABLE_NAME);
        buffer = addPrimaryKey(buffer);
        buffer = addCreateColumn(buffer, TYPE_TEXT, FIELD_NAME);
        buffer = addCreateColumn(buffer, TYPE_TEXT, FIELD_DESCR);
        _dbHelper.getWritableDatabase().execSQL(buffer);
    }

    public long addPackage(String name, String descr) {
        SQLiteDatabase db = _dbHelper.getWritableDatabase();

        ContentValues values = new ContentValues();
        values.put(FIELD_NAME, name);
        values.put(FIELD_DESCR, descr);

        long id = db.insert(TABLE_NAME, null, values);
        return id;
    }
}
