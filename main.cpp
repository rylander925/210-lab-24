/*
COMSC-210 | Lab 24 | Rylan Der
IDE Used: Visual Studio Code
*/

#include <iostream>
#include <fstream>
#include <iomanip>
#include <list>
#include "Goat.h"
using namespace std;

const int SZ_NAMES = 200, SZ_COLORS = 25, MAX_AGE = 20;
const int IGNORE_STREAM_CHARS = 100;                        //Number of characters ignored when using istream.ignore()

enum Choice { ADD = 1, DELETE = 2, DISPLAY = 3, QUIT = 4 }; //Use enum for options for readability

int select_goat(list<Goat> &trip);
void delete_goat(list<Goat> &trip);
void add_goat(list<Goat> &trip, string names[], string colors[]);
void display_trip(list<Goat>& trip);
Choice main_menu();
void coutline(int size = 30, char fill = '=');

int main() {
    srand(time(0));
    bool again;

    // read & populate arrays for names and colors
    ifstream fin("names.txt");
    string names[SZ_NAMES];
    int i = 0;
    while (fin >> names[i++]);
    fin.close();
    ifstream fin1("colors.txt");
    string colors[SZ_COLORS];
    i = 0;
    while (fin1 >> colors[i++]);
    fin1.close();

    list<Goat> goats;
    Choice choice;
    
    //Call menu function until user quits
    while(choice != QUIT) {
        choice = main_menu();

        //Execute respective function based on choice
        switch(choice) {
            case(ADD):
                cout << "Adding goat..." << endl;
                add_goat(goats, names, colors);
                break;

            case(DELETE):
                cout << "Deleting goat..." << endl;
                delete_goat(goats);
                break;

            case(DISPLAY):
                display_trip(goats);
                break;
        }

        coutline();
    }
    return 0;
}

/**
 * Outputs a line of characters
 * @param size Number of characters in line
 * @param fill Character to use for line
 */
void coutline(int size, char fill) {
    char oldFill = cout.fill();                                         //save old fill character to reset cout after outputting line
    cout << setw(size) << setfill(fill) << "" << setfill(oldFill) << endl ;
}

/**
 * Prompts user to select a goat and deletes selected goat
 * @param trip List of goats
 */
void delete_goat(list<Goat> &trip) {
    if (trip.empty()) { cout << "No goats to delete." << endl; return; }//exit if there are no goats in the list

    int index;
    list<Goat>::iterator it = trip.begin();                             //instantiate iterator at beginning to locate goat

    cout << "Select a goat to delete from list." << endl;
    index = select_goat(trip) - 1;                                      //select_trip returns goat number; need to subtract one to obtain a valid index

    for(int i = 0; i < index; i++, it++);                               //Increment iterator to the chosen goat

    cout << "Removed " << it->get_name() << " from the list." << endl;
    trip.erase(it);
}

/**
 * Displays goats and queries a goat number. Validates input
 * @note Returned number starts from 1
 * @param trip List of goats to select from
 * @return Selected goat number. Ranges from 1 to the number of goats.
 */
int select_goat(list<Goat> &trip) {
    int choice;
    display_trip(trip);

    //validate input; NOTE: choice starts at 1
    do {
        cout << "Enter a goat number --> ";
        cin >> choice;

        if (cin.fail()) {
            cout << "Choice must be an integer" << endl;
            choice = -1;
            cin.clear();
        } else if (choice < 1 || choice > trip.size()) {    //validates input based on number of goats
            cout << "Choice must be between 1 and " << trip.size() << endl;
        }
        cin.ignore(IGNORE_STREAM_CHARS, '\n');
    } while(choice < 1 || choice > trip.size());

    return choice;
}

/**
 * Adds a new goat to a list of goats.
 * Goat is given a random name and color out of the given arrays.
 * @param trip List of goats to add a new goat to
 * @param names Name is chosen out of this array of names
 * @param colors Color is chosen out of this array of colors
 */
void add_goat(list<Goat> &trip, string names[], string colors[]) {
    //select random name, color, age
    string name     = names[rand() % SZ_NAMES];
    string color    = colors[rand() % SZ_COLORS];
    int    age      = 1 + rand() % MAX_AGE;

    //add goat to end of list
    trip.push_back(Goat(name, age, color));

    cout << "Added " << trip.back().get_name() << "!" << endl;
}

/**
 * Displays goat data given a list of goats
 * @param trip List of goats to display
 */
void display_trip(list<Goat>& trip) {
    if (trip.empty()) { cout << "No goats to display." << endl; return; }

    coutline();
    cout << "Goats:" << endl;
    int i = 1;
    //output all goats
    for (Goat goat : trip) {
        cout << "[" << i << "] " << goat.get_name() << " (" << goat.get_age() << ", " << goat.get_color() << ")" << endl;
        ++i;
    }
}

/**
 * Output and receive user input for goat management menu
 * Validates input
 * @return Menu option as an integer: 1=Add, 2=Delete, 3=Output List, 4=Quit
 */
Choice main_menu() {
    int choice;

    //output menu once
    cout << "*** GOAT MANAGER 3001 ***" << endl
         << "[1] Add a goat"            << endl
         << "[2] Delete a goat"         << endl
         << "[3] List goats"            << endl
         << "[4] Quit"                  << endl;
    
    //validate input
    do {
        cout << "Choice --> ";
        cin >> choice;

        if (cin.fail()) {
            cout << "Choice must be an integer" << endl;
            choice = -1;
            cin.clear();
        } else if (choice < 1 || choice > 4) {
            cout << "Choice must be 1, 2, 3, or 4" << endl;
        }
        cin.ignore(IGNORE_STREAM_CHARS, '\n');
    } while(choice < 1 || choice > 4);

    return static_cast<Choice>(choice); //cast integer choice to Choice enum for readability
}

