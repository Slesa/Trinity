package persist;

import android.database.sqlite.SQLiteDatabase;

public class PackageTable extends TableBase {

    private static final String TABLE_NAME = "packages";
    private static final String FIELD_NAME = "name";
    private static final String FIELD_DESCR = "descr";

    public void createTable(SQLiteDatabase db) {
        String buffer = startCreateTable(TABLE_NAME);
        buffer = addPrimaryKey(buffer);
        buffer = addCreateColumn(buffer, TYPE_TEXT, FIELD_NAME);
        buffer = addCreateColumn(buffer, TYPE_TEXT, FIELD_DESCR);
        db.execSQL(buffer);
    }
}
