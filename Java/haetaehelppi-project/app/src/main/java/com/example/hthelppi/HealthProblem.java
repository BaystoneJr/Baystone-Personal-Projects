package com.example.hthelppi;

/**
 * HealthProblem-class is a class to handle a single health problem, that is written in the list of the problems
 * It includes methods to get all the information of a single health problem
 */

public class HealthProblem {
    /**
     * name:String is for the name of the problem
     * description:String is for the description of the health problem
     * questionForBot:String is for the question that the bot asks the user in the ChatBot-component
     * call112:String is to hold the information in which situations users should call 112 (Emergency services)
     * goToEmergencyDuty:String is to hold the information in which users should go to see emergency duty
     * selfCare:String is to hold information on how user could take care of the problem themselves
     * moreInfo:String is to hold information on more information about the problem
     */
    private String name;
    private String description;
    private String questionForBot;
    private String call112;
    private String goToEmergencyDuty;
    private String selfCare;
    private String moreInfo;

    /**
     * Constructor for the HealthProblem-class
     * @param name name of the problem
     * @param description description of the problem
     * @param questionForBot question for the bot to ask
     * @param call112 instructions in which situations users should call emergency services
     * @param goToEmergencyDuty instructions in which situations users should go to see emergency services
     * @param selfCare instructions in which users should take care of the problem themselves
     * @param moreInfo more information about the problem
     */
    public HealthProblem(String name, String description, String questionForBot, String call112, String goToEmergencyDuty, String selfCare, String moreInfo) {
        this.name = name;
        this.description = description;
        this.questionForBot = questionForBot;
        this.call112 = call112;
        this.goToEmergencyDuty = goToEmergencyDuty;
        this.selfCare = selfCare;
        this.moreInfo = moreInfo;
    }

    /**
     * returns name of the problem
     * @return
     */
    public String getName() {
        return this.name;
    }

    /**
     * returns description of the problem
     * @return
     */
    public String getDescription() {
        return this.description;
    }

    /**
     * returns the question for the bot
     * @return
     */
    public String getQuestionForBot() {
        return this.questionForBot;
    }

    /**
     * returns the call112 information of the problem
     * @return
     */
    public String getCall112() {
        return "Soita 112 jos: " + this.call112;
    }

    /**
     * returns the emergency duty instructions of the problemn
     * @return
     */
    public String getGoToEmergencyDuty() {
        return "Hakeudu päivystykseen, jos: " + this.goToEmergencyDuty;
    }

    /**
     * returns self care instructions of the problem
     * @return
     */
    public String getSelfCare() {
        return "Hoida itse: " + this.selfCare;
    }

    /**
     * returns more information about the problem
     * @return
     */
    public String getMoreInfo() {
        return this.moreInfo;
    }

    /**
     * Makes the name of the problem as the to toString-method return, so that the listAdapter show the name only
     * @return
     */
    @Override
    public String toString() {
        return this.name;
    }
}
