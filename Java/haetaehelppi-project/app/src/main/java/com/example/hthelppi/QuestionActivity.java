package com.example.hthelppi;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.TextView;

/**
 * This class is used for the question that the bot asks from the user
 * It starts the QAnswerActivity based on the users answer
 * The questions are always a simple yes or no question
 */

public class QuestionActivity extends AppCompatActivity {
    /**
     * Variable to hold the name of the selected listview item
     */
    private String selectedProblemName;
    /**
     * The intent.putExtra()-method key value
     */
    public static final String QUESTION_ANSWER = "QUESTION_ANSWER";

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_question);
        /**
         * Get the intents extra values
         */
        Bundle b = getIntent().getExtras();
        selectedProblemName = b.getString(MainActivity.HEALTHPROBLEM_SELECTED_NAME);
        /**
         * Find layout textviews
         */
        TextView question = findViewById(R.id.questionTv);
        TextView  questionHeader = findViewById(R.id.questionHeader);

        /**
         * Get the health problem from the singleton class
         */
        HealthProblem healthProblem = HealthProblemAPI.getInstance(this).getSingleHealthProblem(selectedProblemName);
        /**
         * Set texts for the TextViews
         */
        question.setText(healthProblem.getQuestionForBot());
        questionHeader.setText(healthProblem.getName());

    }

    /**
     * Method used to streamline the starting of the next activity, this method starts the QAnswerActivity
     * @param questionAnswer boolean value to put as intent.puExtra()-value. If user answered yes, put true, no, ut false
     * @param selectedName String value for the selected health problem that was clicked on the main activity listview
     */
    public void openNewActivity(boolean questionAnswer, String selectedName){
        Intent intent = new Intent(this, QAnswerActivity.class);
        intent.putExtra(MainActivity.HEALTHPROBLEM_SELECTED_NAME,selectedName);
        intent.putExtra(QUESTION_ANSWER, questionAnswer);
        startActivity(intent);

    }

    /**
     * onClick method to handle the layout's onClick events, so that it sends the correct boolean values for the QAnswerActivity class
     * @param view required parameter that the button onClick method uses, the view is the button that is clicked
     */
    public void onClick(View view) {
        int viewId = view.getId();
        int buttonYesId = R.id.buttonYes;
        int buttonNoId = R.id.buttonNo;

        if(viewId == buttonYesId) {
            openNewActivity(true, selectedProblemName);
        } else if(viewId == buttonNoId) {
            openNewActivity(false, selectedProblemName);
        }
    }
}