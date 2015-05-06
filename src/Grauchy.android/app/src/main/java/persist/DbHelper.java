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
            _packageTable = new PackageTable();
        return _packageTable;
    }

    @Override
    public void onCreate(SQLiteDatabase db) {
        packageTable().createTable(db);
    }

    @Override
    public void onUpgrade(SQLiteDatabase db, int oldVersion, int newVersion) {

    }
}
