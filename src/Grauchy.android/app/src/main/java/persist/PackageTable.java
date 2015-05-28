package persist;

import android.content.ContentValues;
import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;

public class PackageTable extends TableBase {

    private static final String TABLE_NAME = "packages";
    private static final String FIELD_NAME = "name";
    private static final String FIELD_DESCR = "descr";

    private DbHelper _dbHelper;

    public PackageTable(DbHelper dbHelper) {
        _dbHelper = dbHelper;
    }

    public void createTable(SQLiteDatabase db) {
        String buffer = startCreateTable(TABLE_NAME);
        buffer = addPrimaryKey(buffer);
        buffer = addCreateColumn(buffer, TYPE_TEXT, FIELD_NAME);
        buffer = addCreateColumn(buffer, TYPE_TEXT, FIELD_DESCR, true);
        db.execSQL(buffer);
    }

    public long addPackage(String name, String descr) {
        SQLiteDatabase db = _dbHelper.getWritableDatabase();

        ContentValues values = new ContentValues();
        values.put(FIELD_NAME, name);
        values.put(FIELD_DESCR, descr);

        long id = db.insert(TABLE_NAME, null, values);
        return id;
    }

    public int readPackages(IPackageReader reader) {
        String[] projection = {
          FIELD_NAME, FIELD_DESCR
        };
        String sortOrder = FIELD_NAME + DESCENDING;

        SQLiteDatabase db = _dbHelper.getReadableDatabase();
        Cursor c = db.query(TABLE_NAME, projection, null, null, null, null, sortOrder);

        int found = 0;
        for( c.moveToFirst(); c.moveToNext(); found++ ) {
            Package pack = fromCursor(c);
            reader.read(pack);
        }
        return found;
    }

    private Package fromCursor(Cursor c) {
        Package pack = new Package();
        pack.setName(c.getString(c.getColumnIndex(FIELD_NAME)));
        pack.setDescription(c.getString(c.getColumnIndex(FIELD_DESCR)));
        return pack;
    }
}
