package persist;

public class TableBase {
    protected static final String TYPE_TEXT = " TEXT";
    protected static final String TYPE_INT = " INTEGER";
    private static final String COMMA_SEP = ",";
    private static final String PRIMARY_KEY = " PRIMARY KEY";
    protected static final String DESCENDING = " DESC";
    protected static final String ASCENDING = " ASC";
    protected static final String FIELD_ID = "id";

    protected static String getDropTable(String tableName) {
        String buffer = "DROP TABLE IF EXISTS " + tableName;
        return buffer;
    }

    protected static String startCreateTable(String tableName) {
        String buffer = "CREATE TABLE " + tableName + " (";
        return buffer;
    }

    protected static String addPrimaryKey(String cmd) {
        return addPrimaryKey(cmd, false);
    }

    protected static String addPrimaryKey(String cmd, boolean last) {
        String buffer = addCreateColumn(cmd, TYPE_INT + PRIMARY_KEY, FIELD_ID, last);
        return buffer;
    }

    protected static String addCreateColumn(String cmd, String type, String name) {
        return addCreateColumn(cmd, type, name, false);
    }

    protected static String addCreateColumn(String cmd, String type, String name, boolean last) {
        String buffer = cmd +
            name + " " + type;
        if(!last )
            buffer += COMMA_SEP + " ";
        else
            buffer += ")";
        return buffer;
    }

    protected static String endCreateTable(String cmd) {
        String buffer = cmd + " )";
        return buffer;
    }
}
