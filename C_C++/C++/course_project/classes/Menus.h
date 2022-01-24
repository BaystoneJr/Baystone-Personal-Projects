#ifndef PROJECT_MENUNS_INCLUDED
#define PROJECT_MENUS_INCLUDED
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <limits>

using namespace std;

/**
 * @brief Menus is used to create all of the operations for the function and displaying of the menus seen on console;
 * 
 */

class MenuObserver {
    public:
    virtual void Update() = 0;
};

class MenuSubject {
    public:
    virtual void Attach(MenuObserver *mo) = 0;
    virtual void Detach(MenuObserver *mo) = 0;
    virtual void Notify() = 0;
};

class MenuContainer: public MenuSubject {
    public:
    MenuContainer();
    void addString(const string& s);
    int askInputInt(const string &printText, int minValue, int maxValue);
    string askInputString(const string &printText);
    const string& getString(int textPos);
    int getSize();
    void display();
    virtual void Attach(MenuObserver *mo);
    virtual void Detach(MenuObserver *mo);
    virtual void Notify();
    private:
    vector<string> menuTexts;
    vector<MenuObserver*> observers;

};

class MenuWindow : public MenuObserver {
    public:
    MenuWindow(int initalRows, MenuContainer *mc = 0);
    void displayWindow();
    void setSubject(MenuContainer *mc);
    void Update();

    private:
    int rows;
    MenuContainer *mc;
};

#endif