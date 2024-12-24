//A simple program that helps you calculate your budget
#include "BudgetPlanner.h"
#include <iostream> //For basic I/O operation
#include <conio.h>

using namespace std;
void Loading();

const int MAX_ITEMS = 100;// Maximum anticipated number for items in a particular budget

struct Item // A structure for the items we get from the user
{
    string name;
    float price;
};

int main()
{
    Item items[MAX_ITEMS];
    int itemCount;
    float budget;

    cout << "How many items do you want to calculate (max " << MAX_ITEMS << ") ? " << endl;
    cout << "Enter your response here: ";
    cin >> itemCount;
    if (itemCount > MAX_ITEMS || itemCount <= 0) // simple error checker to see if the user inputs a wrong number which is on the boundaries
    {
        cout << "Invalid number of items." << endl;
        red;
        return 1;
    }
    cout << "Enter your budget price: K ";
    cin >> budget;

    float totalExpenses = 0;

    for (int i = 0; i < itemCount ; ++i)
    {
        cout << "Enter the name of the item at position " << i + 1 << " : ";
        cin.ignore();
        getline(cin, items[i].name);
        try // An exception for when the user enters a letter or any character on the keyboard instead of a number.
        {
            cout << "Enter the price of " << items[i].name << ": K ";
            cin >> items[i].price;
            if (items[i].price)
            {
                cout << "." << endl;
            }
            else
            {
                throw(404);
            }
        }
        catch(int wrongInput)
        {
            cout << "Error" << wrongInput << ". You entered a wrong character.Closing program..." << endl;
            red;
            Sleep(500);
            exit(0);
        }
        cout << endl << endl;
        totalExpenses += items[i].price;
    }

    cout << "\nTotal Expenses: K " << totalExpenses << endl;
    float remaining = budget - totalExpenses;
    if (remaining >= 0)
    {
        cout << "You are within budget." << endl << endl;
    }
    else
    {
        cout << "You are over the budget." << endl << endl;
        red;
    }
    cout << "Remaining amount: K " << remaining << endl;
    cout << "\nPress any key to exit the program." << endl;
    getch();
    Loading();
    cout << "\n\n\n\t\tThank you for using the program." << endl;

    return 0;
}


