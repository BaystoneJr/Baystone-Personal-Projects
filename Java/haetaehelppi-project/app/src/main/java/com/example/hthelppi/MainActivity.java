package com.example.hthelppi;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.appcompat.app.AppCompatActivity;

import android.content.Context;
import android.content.Intent;
import android.os.Bundle;
import android.text.Editable;
import android.text.TextWatcher;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.view.ViewGroup;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.EditText;
import android.widget.ListView;
import android.widget.Toast;

import androidx.appcompat.widget.Toolbar;

import java.util.ArrayList;
import java.util.Arrays;

/**
 * MainActivity-class
 * This is the MainActivity-class that is the main activity for the application
 * It also works as the first activity of the ChatBot-component
 * From this activity you can either go to to the Problem Library-Activity through the toolbar
 * or go
 */


public class MainActivity extends AppCompatActivity {
    /**
     * Used for the intent.putExtra()-key value
     */
    public static final String HEALTHPROBLEM_SELECTED_NAME = "HEALTHPROBLEM_SELECTED_NAME";
    /**
     * List view
     */
    private ListView lv;

    /**
     * Listview Adapter
     */
    ArrayAdapter<String> adapter;

    /**
     * Search EditText
     */
    EditText inputSearch;

    /**
     * ArrayList for Listview
     */
    ArrayList<String> adapterArrayList;

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        /**
         * Sets the toolbar for the activity
         */
        Toolbar myToolbar = findViewById(R.id.toolbarMainActivity);
        setSupportActionBar(myToolbar);

        /**
         * Gets the names of the health problems as String array
         */
        String[] healthProblemNamesArray = HealthProblemAPI.getInstance(this).getHealthProblemNames();

        lv = (ListView) findViewById(R.id.list_view);
        inputSearch = (EditText) findViewById(R.id.inputSearch);

        adapterArrayList = new ArrayList<>(Arrays.asList(healthProblemNamesArray));
        /**
         * set adapter value as anonymized ArrayAdapter with the correct list_item and id of the textview in the list item and it takes the healthProblems array as the array values for the list
         * getView method is used to change the color values of the list items, so that every other value is light gray and every other is white
         */
        adapter = (new ArrayAdapter<String>(this, R.layout.list_item, R.id.oireet, healthProblemNamesArray){
            @NonNull
            @Override
            public View getView(int position, @Nullable View convertView, @NonNull ViewGroup parent) {
                View view = super.getView(position, convertView, parent);
                if(position %2==1){
                    view.setBackgroundColor(getColor(R.color.white));
                }else {
                    view.setBackgroundColor(getColor(R.color.light_grey));
                }
                return view;
            }

        });
        /**
         * Enables TextFilter for listview and sets the adapter for the listview
         */
        lv.setTextFilterEnabled(true);
        lv.setAdapter(adapter);


        /**
         * Enabling Search Filter
         * This is the functionality to enable the search function of the main activity
         * It only requires the onTextChanged but others have to be implemented as empty methods
         * This updates the list dataset based on the input of the user in the inputSearch-EditText
         * */
        inputSearch.addTextChangedListener(new TextWatcher() {

            @Override
            public void onTextChanged(CharSequence cs, int arg1, int arg2, int arg3) {
                // Change dataset based on the input of the user, the user input is in the cs parameter
                MainActivity.this.adapter.getFilter().filter(cs);
                adapter.notifyDataSetChanged();
            }

            @Override
            public void afterTextChanged(Editable editable) {

            }

            @Override
            public void beforeTextChanged(CharSequence arg0, int arg1, int arg2,
                                          int arg3) {

            }

        });
        /**
         * This is the ClickListener for the listView items. It basically reacts, when user presses any item on the list
         * It first checks if the health problem that user clicked on has a question or not, if there is a question, it opens the QuestionActivity
         * if there is no question, it opens the QAnswerActivity class
         * putExtra values are for the activities to handle the health problem correctly
         */
        lv.setOnItemClickListener(new AdapterView.OnItemClickListener() {
            @Override
            public void onItemClick(AdapterView<?> parent, View view, int position, long id) {
                HealthProblem problem = HealthProblemAPI.getInstance(MainActivity.this).getSingleHealthProblem(position);
                String problemQuestion = problem.getQuestionForBot();

                Intent intent;

                String itemPositionName = parent.getItemAtPosition(position).toString();


                if(problemQuestion.equals("-")) {
                    intent = new Intent(MainActivity.this, QAnswerActivity.class);
                    intent.putExtra(HEALTHPROBLEM_SELECTED_NAME, itemPositionName);
                    intent.putExtra(QuestionActivity.QUESTION_ANSWER, true);
                } else {
                    intent = new Intent(MainActivity.this, QuestionActivity.class);
                    intent.putExtra(HEALTHPROBLEM_SELECTED_NAME,itemPositionName);
                }
                startActivity(intent);
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
                intent = new Intent(MainActivity.this, MainActivity.class);
                startActivity(intent);
                return true;
            case R.id.menuItemProblemLibrary:
                intent = new Intent(MainActivity.this, ProblemLibrary.class);
                startActivity(intent);
                return true;
            case R.id.menuItemHelpCenterButton:
                Context context = getApplicationContext();
                CharSequence text = getString(R.string.helpCenterMessageMainActivity);
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