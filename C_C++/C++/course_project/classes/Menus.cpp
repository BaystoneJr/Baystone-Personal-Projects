#include "Menus.h"

MenuContainer::MenuContainer() { }

void MenuContainer::addString(const string& s) {
    menuTexts.push_back(s);
    Notify();
}

const string& MenuContainer::getString(int textPos) {
    return menuTexts.at(textPos);
}

int MenuContainer::getSize() {
    return menuTexts.size();
}

void MenuContainer::Attach(MenuObserver *o) {
    observers.push_back(o);
}

void MenuContainer::Detach(MenuObserver *o) {
    observers.pop_back();
}
void MenuContainer::Notify() {
    for(int i = 0; i < observers.size() ; i++) {
        observers[i]->Update();
    }
}

int MenuContainer::askInputInt(const string &printText, int minValue, int maxValue) {
    int inputValue;

    cout << printText;

    cin >> inputValue;

    while ((cin.fail()) || (inputValue > maxValue || inputValue < minValue))
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "Value, you tried to enter is incorrect, please enter correct value: ";

        cin >> inputValue;
    }

    cin.ignore();
    
    return inputValue;
}
string MenuContainer::askInputString(const string &printText) {
    string userInput;

    cin.sync();

    cout << printText;

    getline(cin, userInput);

    return userInput;
}

MenuWindow::MenuWindow(int initialRows, MenuContainer *mc) {
    rows = initialRows;
}

void MenuWindow::displayWindow() {
    int firstRow;
    cout << "----------------" << endl;
    if(mc->getSize() < rows) {
        for(int i = 0; i < mc->getSize(); i++) {
            cout << mc->getString(i) << endl;
        }
    } else {
        firstRow = mc->getSize() - rows;
        for(int i = 0; i < rows; i++) {
            cout << mc->getString(firstRow + i) << endl; 
        }
    }
    cout << "----------------" << endl;
}

void MenuWindow::setSubject(MenuContainer *mc) {
    this->mc = mc;
}

void MenuWindow::Update() {
    displayWindow();
}