package com.example.hthelppi;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.widget.TextView;

/**
 * This activity class shows the Problem library's detailed view
 * It opens up when user clicks an item on the problem library list view
 * It also opens through the QAnswerActivity when users clicks the button to see more information
 * The purpose of this class is to show all of the information that the application has about the specific health problem
 */

public class ProblemLibraryDetails extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_problem_library_details);
        /**
         * Reads the intent extra values for the index of the list item
         */
        Bundle b = getIntent().getExtras();
        int ind = b.getInt(ProblemLibrary.PROBLEM_INDEX, 0);
        /**
         * Find the layout widgets
         */
        TextView header = findViewById(R.id.problemName); //Problem name
        TextView descripiton = findViewById(R.id.descriptionTextView); //Problem description
        TextView call112 = findViewById(R.id.call112TextView); //Problem Call112 instructions
        TextView emergencyDuty = findViewById(R.id.paivystysTextView); //Emergency duty instructions
        TextView selfCare = findViewById(R.id.selfCareTextView); //Self care instructions
        TextView moreInfo = findViewById(R.id.moreInfoTextView); // More information

        /**
         * Set the values for the text views
         * a. Get API singleton instance
         */
        HealthProblemAPI problemAPI = HealthProblemAPI.getInstance(this);
        /**
         * b. Get the Health Problem object from API Singleton class
         */
        HealthProblem problem = problemAPI.getSingleHealthProblem(ind);
        /**
         * c. set the objects values to the textViews
         */
        header.setText(problem.getName());
        descripiton.setText(problem.getDescription());
        call112.setText(problem.getCall112());
        emergencyDuty.setText(problem.getGoToEmergencyDuty());
        selfCare.setText(problem.getSelfCare());
        moreInfo.setText(problem.getMoreInfo());


    }
}