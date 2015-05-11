package com.solutions.slesa.grauchy;

import android.app.Activity;
import android.os.Bundle;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.EditText;
import android.widget.Spinner;

import java.util.ArrayList;
import java.util.List;

import persist.DbHelper;

// http://www.mkyong.com/android/android-spinner-drop-down-list-example/
// http://developer.android.com/guide/topics/ui/controls/spinner.html

public class MainActivity extends Activity implements AdapterView.OnItemSelectedListener {

    DbHelper _dbHelper;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        _dbHelper = new DbHelper(getApplicationContext());
        DemoData demoData = new DemoData(_dbHelper);
        demoData.createDemoData();

        addItemsOnPackages();
    }

    private void addItemsOnPackages() {
        Spinner spinner = (Spinner) findViewById(R.id.spinPackage);

        List<String> list = new ArrayList<String>();
        list.add("Visual Studio");
        list.add("Resharper");
        list.add("Vim");
        list.add("Zsh");
        ArrayAdapter<String> dataAdapter = new ArrayAdapter<String>(this, android.R.layout.simple_spinner_item, list);
        dataAdapter.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);
        spinner.setAdapter(dataAdapter);
        spinner.setOnItemSelectedListener(this);
    }

    public void onItemSelected(AdapterView<?> parent, View view, int pos, long id) {
        // An item was selected. You can retrieve the selected item using
        // parent.getItemAtPosition(pos)
        String item = (String) parent.getItemAtPosition(pos);
        EditText editbox = (EditText) findViewById(R.id.editSearch);
        editbox.setText(item);
    }

    public void onNothingSelected(AdapterView<?> parent) {
        // Another interface callback
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.menu_main, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        // Handle action bar item clicks here. The action bar will
        // automatically handle clicks on the Home/Up button, so long
        // as you specify a parent activity in AndroidManifest.xml.
        int id = item.getItemId();

        //noinspection SimplifiableIfStatement
        if (id == R.id.action_settings) {
            return true;
        }

        return super.onOptionsItemSelected(item);
    }
}
