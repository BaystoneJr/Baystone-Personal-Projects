package com.example.hthelppi;
/**
 * HealthProblemAPI-class is a singleton class to handle the list of the problems
 * It handles the healthproblems from the list of all of the health problems and returns information about the health problems
 * It uses Context package to get the String resources from the healthproblems.xml-file
 */


import android.content.Context;

import java.util.ArrayList;
import java.util.List;

public class HealthProblemAPI {
    /**
     * problemList:List<HealthProblem> to hold all the healthProblems
     */
    private List<HealthProblem> problemList;


    /**
     * private constructor to build the list of the health problems
     * @param context context is required to access the resources of the application
     */
    private HealthProblemAPI(Context context) {
        /**
         * Gets the string-array that holds the resource names of all the health problem string-arrays
         * and iniates the problemList as ArrayList
         */
        String[] healthProblemArrayNames = context.getResources().getStringArray(R.array.healthProblemNames);
        problemList = new ArrayList<>();

        /**
         * For-loop is used to put all of the health problems in to the problemList
         * For every healthProblem-object it first gets the problems string-array resource name from the string-array that holds the names of all the problem string-arrays resource names
         * And by using that name, it finds the single health problem string-array resource
         * After getting the string-array resource, it uses the values of the resource to create the healthProblem-objects
         * After the object has been initialized, it is added to the problemList
         *
         * To read which resource-item goes to in the initializer, read the comments on the healthproblems.xml-file
         */
        for (String problemArrayName : healthProblemArrayNames) {
            int healthProblemArrayId = context.getResources().getIdentifier(problemArrayName, "array",context.getPackageName());
            String[] healthProblemStrings = context.getResources().getStringArray(healthProblemArrayId);
            HealthProblem healthProblem = new HealthProblem(healthProblemStrings[0], healthProblemStrings[1], healthProblemStrings[2], healthProblemStrings[3], healthProblemStrings[4],
                    healthProblemStrings[5], healthProblemStrings[6]);
            problemList.add(healthProblem);
        }

    }

    /**
     * This method is used to return the instance of the class
     * @param context context is required to get the resource strings for the problems
     * @return HealthProblemAPI instance
     */
    public static HealthProblemAPI getInstance(Context context) {
        return new HealthProblemAPI(context);
    }

    /**
     * Returns the problem list
     * @return list of all the health problems
     */
    public List<HealthProblem> getProblemList() {
        return problemList;
    }

    /**
     * Method to get the names of the healthProblems in List of Strings
     * @return String-list of the health problem names
     */
    public List<String> getHealthNames() {
        List<String> problemNamesList = new ArrayList<>();
        for (HealthProblem healthProblem : problemList) {
            problemNamesList.add(healthProblem.getName());
        }
        return problemNamesList;
    }

    /**
     * Gets the names of the health problems as string array
     * @return health problem names as String array
     */
    public String[] getHealthProblemNames() {
        String[] healthNames = new String[problemList.size()];

        for (int i = 0; i < problemList.size(); i++) {
            HealthProblem healthProblem = problemList.get(i);

            healthNames[i] = healthProblem.getName();
        }

        return healthNames;
    }

    /**
     * Method to get single health problem for the problem list by its index-value
     * @param index index of the single health problem
     * @return HealthProblem-object tha corresponds to the index given as parameter
     */
    public HealthProblem getSingleHealthProblem(int index) {
        HealthProblem healthProblem = problemList.get(index);

        return healthProblem;
    }

    /**
     * Returns single health problem as object based on the name of the health problem
     * @param name name of the single health problem, that is wanted
     * @return Corresponding health problem, if not found, returns null
     */
    public HealthProblem getSingleHealthProblem(String name) {
        HealthProblem healthProblem = null;

        for(HealthProblem problem : problemList) {
           if(problem.getName().equals(name)) {
               healthProblem = problem;
               break;
           }
        }

        return healthProblem;
    }

    /**
     * Method to get the index of the single health problem
     * @param problem HealthProblem object of which index needs to be found
     * @return returns integer value of index
     */
    public int getHealthProblemIndex(HealthProblem problem) {
        int indexOf;

        indexOf = problemList.indexOf(problem);

        return indexOf;
    }

}
