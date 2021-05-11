package com.example.hthelppi;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

/**
 * This class is to show the answer for the question
 * This activity either opens through the question activity or the main activity, depending on whether the health problem
 * has a question or not
 */
public class QAnswerActivity extends AppCompatActivity {
    /**
     * name of the problem selected from the list view
     */
    private String selectedProblemName;
    /**
     * object of the selected list view item
     */
    private HealthProblem selectedHealthProblem;
    /**
     * Index of the selected list view item
     */
    private int selectedProblemIndex;
    /**
     * Instance reference for the HealthProblemAPI class
     */
    private HealthProblemAPI healthProblemAPI;
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_q_answer);
        /**
         * Get the extra values from the intent bundle
         */
        Bundle b = getIntent().getExtras();
        selectedProblemName = b.getString(MainActivity.HEALTHPROBLEM_SELECTED_NAME);
        boolean needsToCall911 = b.getBoolean(QuestionActivity.QUESTION_ANSWER);
        /**
         * Set up of the layout widgets
         */
        TextView questionAnswer = findViewById(R.id.questionAnswer);
        TextView  questionHeader = findViewById(R.id.answerHeader);
        Button moreInfoButton = findViewById(R.id.getMoreInfoButton);
        /**
         * get instance of HealthProblemAPI
         */
        healthProblemAPI = HealthProblemAPI.getInstance(this);
        /**
         * Get index of the health problem and the health problem object
         */
        selectedHealthProblem = healthProblemAPI.getSingleHealthProblem(selectedProblemName);
        selectedProblemIndex = healthProblemAPI.getHealthProblemIndex(selectedHealthProblem);
        /**
         * Set text for the textViews and buttons based on the boolean values
         */
        questionHeader.setText(selectedHealthProblem.getName());
        moreInfoButton.setText(selectedHealthProblem.getName());
        if(needsToCall911) {
            questionAnswer.setText(selectedHealthProblem.getCall112());
        }else{
            questionAnswer.setText(selectedHealthProblem.getGoToEmergencyDuty());
        }

    }
    /**
     * onClick method to handle the button press on the activity layout to open more info on the selected health problem
     * @param view required parameter for the onClick-method to work, the view is used to identify and interact with the button
     */
    public void onClick(View view) {
        Intent intent = new Intent(this, ProblemLibraryDetails.class);
        intent.putExtra(ProblemLibrary.PROBLEM_INDEX, selectedProblemIndex);
        startActivity(intent);
    }
}