#ifndef BUDGETPLANNER_H_INCLUDED
#define BUDGETPLANNER_H_INCLUDED

#include <cstdlib>
#include <iostream>
#include <windows.h>
#include <conio.h>
#include <string>
#include <fstream>

#define red system("color 4") // we define color red to  be used when errors are displayed
#define green system("color a")

using namespace std;


void Login()
{
    string username = "Carlos20", password = "LovesC#";
    string getUser, getPassword;

    cout << "\t\tWelcome to the Budget Planner" <<endl << endl;
    cout << "Enter your user name: ";
    cin >> getUser;
    cout << "Enter your password: ";
    cin >> getPassword;

    if (getUser == username && getPassword == password)
    {
        cout << "Correct credentials." << endl;
    }
    else
    {
        cout << "Wrong credentials." << endl;
        exit(0);
    }
}

#endif // BUDGETPLANNER_H_INCLUDED
