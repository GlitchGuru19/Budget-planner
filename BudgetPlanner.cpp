//A simple program that helps you calculate your budget
#include "BudgetPlanner.h"
#include "Loading.h"

using namespace std;

const int MAX_ITEMS = 100; // Maximum number of items

class Item {
private:
    string name; // Item name
    float price; // Item price

public:
    // Constructor
    Item() : name(""), price(0.0f) {}

    // Getters
    string getName() const { return name; }
    float getPrice() const { return price; }

    // Setters
    void setName(string n) {
        if (!n.empty()) {
            name = n;
        }
    }
    void setPrice(float p) {
        if (p >= 0) {
            price = p;
        }
    }
};

class BudgetPlanner {
private:
    Item items[MAX_ITEMS]; // Array of items
    int itemCount;         // Number of items
    float budget;          // User budget
    float totalExpenses;   // Total cost of items
    string date;           // Purchase date
    string filename;       // Output file name

    // Validate inputs
    bool isValidItemCount(int count) const {
        if (count <= 0 || count > MAX_ITEMS) {
            cout << "Invalid number of items.\n";
            return false;
        }
        return true;
    }

    bool isValidBudget(float b) const {
        if (b < 0) {
            cout << "Budget cannot be negative.\n";
            return false;
        }
        return true;
    }

    bool isValidDate(string d) const {
        if (d.empty()) {
            cout << "Date cannot be empty.\n";
            return false;
        }
        return true;
    }

public:
    // Constructor
    BudgetPlanner() : itemCount(0), budget(0.0f), totalExpenses(0.0f), date(""), filename("budget.txt") {}

    // Input budget, date, and items
    bool inputBudgetAndItems() {
        cout << "Enter purchase date (e.g., 2025-05-17): ";
        getline(cin, date);
        if (!isValidDate(date)) {
            return false;
        }

        cout << "How many items do you want to calculate (max " << MAX_ITEMS << ")?\n";
        cout << "Enter your response here: ";
        cin >> itemCount;
        cin.ignore(); // Clear newline
        if (!isValidItemCount(itemCount)) {
            red;
            return false;
        }

        cout << "Enter your budget price: K ";
        cin >> budget;
        cin.ignore(); // Clear newline
        if (!isValidBudget(budget)) {
            red;
            return false;
        }

        for (int i = 0; i < itemCount; ++i) {
            string name;
            float price;
            cout << "Enter the name of the item at position " << i + 1 << ": ";
            getline(cin, name);
            if (name.empty()) {
                cout << "Item name cannot be empty.\n";
                red;
                return false;
            }

            try {
                cout << "Enter the price of " << name << ": K ";
                cin >> price;
                cin.ignore(); // Clear newline
                if (cin.fail() || price < 0) {
                    throw(404);
                }
                items[i].setName(name);
                items[i].setPrice(price);
                cout << ".\n\n";
            } catch (int wrongInput) {
                cout << "Error " << wrongInput << ". You entered a wrong character. Closing program...\n";
                red;
                Sleep(500);
                exit(0);
            }
        }
        return true;
    }

    // Calculate total expenses and remaining budget
    void calculateBudget() {
        totalExpenses = 0;
        for (int i = 0; i < itemCount; ++i) {
            totalExpenses += items[i].getPrice();
        }
    }

    // Save items and date to file
    bool saveToFile() {
        ofstream file(filename, ios::app);
        if (!file.is_open()) {
            cout << "Error: Cannot open file for writing.\n";
            return false;
        }

        file << "Date: " << date << "\n";
        for (int i = 0; i < itemCount; ++i) {
            file << items[i].getName() << ": K " << items[i].getPrice() << "\n";
        }
        file << "Total Expenses: K " << totalExpenses << "\n";
        file << "----\n";
        file.close();
        return true;
    }

    // Display results
    void displayResults() {
        cout << "\nPurchases for " << date << ":\n";
        cout << "Total Expenses: K " << totalExpenses << "\n";
        float remaining = budget - totalExpenses;
        if (remaining >= 0) {
            cout << "You are within budget.\n\n";
        } else {
            cout << "You are over the budget.\n\n";
            red;
        }
        cout << "Remaining amount: K " << remaining << "\n";
        cout << "\nPress any key to exit the program.\n";
        getch();
        Loading();
        cout << "\n\n\n\t\tThank you for using the program.\n";
    }

    // Run the budgeting process
    void run() {
        cout << "\nWelcome to the Budget Planner\n";
        cout << "---------------------------\n\n";
        if (inputBudgetAndItems()) {
            calculateBudget();
            if (!saveToFile()) {
                cout << "Warning: Failed to save to file, continuing...\n";
            }
            displayResults();
        } else {
            cout << "Program terminated due to invalid input.\n";
            red;
            getch();
            Loading();
            cout << "\n\n\n\t\tThank you for using the program.\n";
        }
    }
};

int main()
{
    BudgetPlanner planner;
    planner.run();
    return 0;
}
