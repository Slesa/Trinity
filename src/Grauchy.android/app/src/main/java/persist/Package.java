package persist;

public class Package {

    private String _name;
    private String _descr;

    public Package() {
    }

    public String getName() { return _name; }
    public void setName(String name) { _name = name; }
    public String getDescription() { return _descr; }
    public void setDescription(String descr) { _descr = descr; }
}
