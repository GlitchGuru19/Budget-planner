#ifndef LOADING_H_INCLUDED
#define LOADING_H_INCLUDED

#include <iostream>
#include <cstdlib>
#include <windows.h>


void Loading () //This function displays loading on the screen when moving from one menu to the next
{
        system ("cls");
        cout << "\n\n\n\t\t\t\tLoading.";
        Sleep(100);                         // The "Sleep" function causes the program output to delay(pause)
        system ("cls");                     // before it is cleared and new output is displayed
        cout << "\n\n\n\t\t\t\tLoading..";  // "system ("cls")" is a function that clears the previous output on the screen
        Sleep(100);                         // before new output is displayed
        system ("cls");
        cout << "\n\n\n\t\t\t\tLoading...";
        Sleep(100);
        system ("cls");
        cout << "\n\n\n\t\t\t\tLoading....";
        Sleep(100);
        system ("cls");
        cout << "\n\n\n\t\t\t\tLoading.....";
        Sleep(100);
        system ("cls");
        cout << "\n\n\n\t\t\t\tLoading......";
        Sleep(100);
        system ("cls");
        cout << "\n\n\n\t\t\t\tLoading.......";
        Sleep(100);
        system ("cls");
        cout << "\n\n\n\t\t\t\tLoading.........";
        Sleep(800);
        system ("cls");
}


#endif // LOADING_H_INCLUDED
