package com.example.hthelppi;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.appcompat.app.AppCompatActivity;

import android.content.Context;
import android.content.Intent;
import android.os.Bundle;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.view.ViewGroup;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.ListView;
import android.widget.Toast;

import androidx.appcompat.widget.Toolbar;

/**
 * This is activity class is the acticity that handles the problem library-component of the application
 */

public class ProblemLibrary extends AppCompatActivity {
    /**
     * intent.putExtra()-key value
     */
    public static final String PROBLEM_INDEX = "PROBLEM_INDEX";
    /**
     * ArrayAdapter variable for listview
     */
    private ArrayAdapter<HealthProblem> adapter;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_problem_library);
        /**
         * Values to setup toolbar
         */
        Toolbar toolbar = (Toolbar) findViewById(R.id.toolbarProblemLibrary);
        setSupportActionBar(toolbar);

        /**
         * ListView setup
         * a. Reference to listView
         */
        ListView lv = findViewById(R.id.lvOngelmaKirjasto);
        /**
         * b. Reference to API-singleton class
         */
        HealthProblemAPI problemAPI = HealthProblemAPI.getInstance(this);

        /**
         * set adapter value as anonymized ArrayAdapter with the correct list_item and id of the textview in the list item and it takes the healthProblems array as the array values for the list
         * getView method is used to change the color values of the list items, so that every other value is light gray and every other is white
         */
        adapter = (new ArrayAdapter<HealthProblem>(this, R.layout.list_item, R.id.oireet, problemAPI.getProblemList()){
            @NonNull
            @Override
            public View getView(int position, @Nullable View convertView, @NonNull ViewGroup parent) {
                View view = super.getView(position, convertView, parent);
                if(position %2==1){
                    view.setBackgroundColor(getColor(android.R.color.white));
                }else {
                    view.setBackgroundColor(getColor(R.color.light_grey));
                }
                return view;
            }

        });
        /**
         * sets the adapter as the listview's adapter
         */
        lv.setAdapter(adapter);

        /**
         * This is the ClickListener for the listView items. It basically reacts, when user presses any item on the list
         * It first checks if the health problem that user clicked on has a question or not, if there is a question, it opens the QuestionActivity
         * if there is no question, it opens the QAnswerActivity class
         * putExtra values are for the activities to handle the health problem correctly
         */
        lv.setOnItemClickListener(new AdapterView.OnItemClickListener() {
            @Override
            public void onItemClick(AdapterView<?> adapterView, View view, int i, long l) {
                Intent nextActivity = new Intent(ProblemLibrary.this,
                        ProblemLibraryDetails.class);
                nextActivity.putExtra(PROBLEM_INDEX, i);
                startActivity(nextActivity);
            }
        });
    }
    /**
     * This method is used to handle the events of the toolbar, so that when user clicks the menu items of the toolbar, it handles the events correctly
     * This method is called when user clicks a toolbar menu item
     * The switch case uses the id of the item param to handle correctly for the item select event
     * @param item item param is the reference to a menu item
     * @return a boolean value, so that the menu item is handled correctly
     */
    @Override
    public boolean onOptionsItemSelected(@NonNull MenuItem item) {
        Intent intent;
        switch (item.getItemId()) {
            case R.id.menuItemChatBot:
                intent = new Intent(ProblemLibrary.this, MainActivity.class);
                startActivity(intent);
                return true;
            case R.id.menuItemProblemLibrary:
                intent = new Intent(ProblemLibrary.this, ProblemLibrary.class);
                startActivity(intent);
                return true;
            case R.id.menuItemHelpCenterButton:
                Context context = getApplicationContext();
                CharSequence text = getString(R.string.helpCenterMessageProblemLibrary);
                int duration = Toast.LENGTH_LONG;
                Toast.makeText(context, text, duration).show();
                return true;
            default:
                return super.onOptionsItemSelected(item);
        }

    }
    /**
     * Method to correctly display the menu of the toolbar
     * It basically inflates the toolbar with the menu set in the menu-layout file
     * @param menu menu param is the param for the selected toolbars menu
     * @return the upper class handles the menu value
     */
    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        getMenuInflater().inflate(R.menu.actionbarmenu, menu);
        return super.onCreateOptionsMenu(menu);
    }
}