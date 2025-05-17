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
    bool isValidBudget(float b) const {
        if (b < 0) {
            cout << "Budget cannot be negative.\n";
            return false;
        }
        return true;
    }

    bool isValidDateFormat(string d) const {
        // Check length (DD-MM-YYYY = 10 characters)
        if (d.length() < 10) {
            return false;
        }
        // Check hyphens at positions 2 and 5
        if (d[2] != '-' || d[5] != '-') {
            return false;
        }
        // Basic format check: DD-MM-YYYY
        for (int i = 0; i < 10; i++) {
            if (i == 2 || i == 5) continue; // Skip hyphens
            if (!isdigit(d[i])) {
                return false; // Non-digit found
            }
        }
        // Extract day, month, year
        string dayStr = d.substr(0, 2);
        string monthStr = d.substr(3, 2);
        string yearStr = d.substr(6, 4);
        int day = stoi(dayStr);
        int month = stoi(monthStr);
        int year = stoi(yearStr);
        // Basic range checks
        if (day < 1 || day > 31) {
            return false;
        }
        if (month < 1 || month > 12) {
            return false;
        }
        if (year < 2000) {
            return false;
        }
        return true;
    }

    bool isValidDate(string d) const {
        if (d.empty()) {
            cout << "Date cannot be empty.\n";
            return false;
        }
        if (!isValidDateFormat(d)) {
            cout << "Invalid date format. Please use DD-MM-YYYY (e.g., 17-05-2025).\n";
            return false;
        }
        return true;
    }

    bool isValidResponse(char r) const {
        return (r == 'y' || r == 'Y' || r == 'n' || r == 'N');
    }

    // Helper to handle exit sequence
    void exitProgram()
    {
        cout << "\nPress any key to exit the program.\n";
        getch();
        Loading();
        cout << "\n\n\n\t\tThank you for using the program.\n";
    }

public:
    // Constructor
    BudgetPlanner() : itemCount(0), budget(0.0f), totalExpenses(0.0f), date(""), filename("budget.txt") {}

    // Destructor
    ~BudgetPlanner() {
        // No dynamic resources to clean up
        itemCount = 0;
        budget = 0.0f;
        totalExpenses = 0.0f;
        date = "";
    }

    // Input budget, date, and items dynamically
    bool inputBudgetAndItems() {
        int attempts = 3;
        while (attempts > 0) {
            cout << "Enter purchase date (e.g., 17-05-2025): ";
            getline(cin, date);
            if (isValidDate(date)) {
                break;
            }
            attempts--;
            cout << "Please try again (" << attempts << " attempts remaining).\n";
        }
        if (attempts == 0) {
            return false;
        }

        attempts = 3;
        while (attempts > 0) {
            cout << "Enter your budget price: K ";
            cin >> budget;
            cin.ignore(); // Clear newline
            if (isValidBudget(budget)) {
                break;
            }
            attempts--;
            cout << "Please try again (" << attempts << " attempts remaining).\n";
        }
        if (attempts == 0) {
            return false;
        }

        itemCount = 0;
        while (itemCount < MAX_ITEMS) {
            string name;
            float price;
            cout << "Enter item " << itemCount + 1 << " name (or press Enter to finish): ";
            getline(cin, name);
            if (name.empty()) {
                break; // User wants to stop
            }

            attempts = 3;
            while (attempts > 0) {
                try {
                    cout << "Enter the price of " << name << ": K ";
                    cin >> price;
                    cin.ignore(); // Clear newline
                    if (cin.fail() || price < 0) {
                        throw(404);
                    }
                    items[itemCount].setName(name);
                    items[itemCount].setPrice(price);
                    cout << ".\n\n";
                    itemCount++;
                    break;
                } catch (int wrongInput) {
                    cin.clear();
                    cin.ignore(10000, '\n'); // Clear bad input
                    attempts--;
                    cout << "Error " << wrongInput << ". Invalid price. Please try again (" << attempts << " attempts remaining).\n";
                }
            }
            if (attempts == 0) {
                return false;
            }

            char response;
            do {
                cout << "Add another item? (y/n): ";
                cin >> response;
                cin.ignore(); // Clear newline
                if (!isValidResponse(response)) {
                    cout << "Please enter 'y' or 'n'.\n";
                }
            } while (!isValidResponse(response));
            if (response != 'y' && response != 'Y') {
                break;
            }
        }

        if (itemCount == 0) {
            cout << "No items entered.\n";
            return false;
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

    // Save items and date to file with exception handling
    bool saveToFile() {
        try {
            ofstream outFile(filename, ios::app);
            if (!outFile.is_open()) {
                throw ios_base::failure("Cannot open file for writing");
            }

            outFile << "Date: " << date << "\n";
            outFile << "Budget: K " << budget << "\n";
            for (int i = 0; i < itemCount; ++i) {
                outFile << items[i].getName() << ": K " << items[i].getPrice() << "\n";
            }
            outFile << "Total Expenses: K " << totalExpenses << "\n";
            outFile << "Remaining: K " << (budget - totalExpenses) << "\n";
            outFile << "----\n";
            outFile.close();
            return true;
        } catch (const ios_base::failure& e) {
            cout << "Error: Failed to write to file (" << e.what() << ").\n";
            return false;
        }
    }

    // Display results
    void displayResults() {
        cout << "\nPurchases for " << date << ":\n";
        cout << "Budget: K " << budget << "\n";
        cout << "Items:\n";
        for (int i = 0; i < itemCount; ++i) {
            cout << "  " << i + 1 << ". " << items[i].getName() << ": K " << items[i].getPrice() << "\n";
        }
        cout << "Total Expenses: K " << totalExpenses << "\n";
        float remaining = budget - totalExpenses;
        if (remaining >= 0) {
            cout << "You are within budget.\n\n";
        } else {
            cout << "You are over the budget.\n\n";
            red;
        }
        cout << "Remaining amount: K " << remaining << "\n";
        exitProgram();
    }

    // Display budget history from file
    bool displayHistory() {
        try {
            ifstream inFile(filename);
            if (!inFile.is_open()) {
                throw ios_base::failure("Cannot open file for reading");
            }

            cout << "\nBudget History:\n";
            cout << string(50, '-') << "\n";
            string line;
            while (getline(inFile, line)) {
                cout << line << "\n";
            }
            cout << string(50, '-') << "\n";
            inFile.close();
        } catch (const ios_base::failure& e) {
            cout << "Error: Failed to read file (" << e.what() << "). File may not exist yet.\n";
        }

        cout << "Press any key to continue.\n";
        getch();

        char response;
        do {
            cout << "Do you want to quit? (y/n): ";
            cin >> response;
            cin.ignore(); // Clear newline
            if (!isValidResponse(response)) {
                cout << "Please enter 'y' or 'n'.\n";
            }
        } while (!isValidResponse(response));
        return (response == 'y' || response == 'Y');
    }

    // Run the budgeting process
    void run() {
        cout << "\nWelcome to the Budget Planner\n";
        cout << "---------------------------\n\n";
        char choice;
        do {
            cout << "1. Add Budget\n2. View History\n3. Exit\n";
            cout << "Enter choice (1-3): ";
            cin >> choice;
            cin.ignore(); // Clear newline
            if (choice == '1') {
                if (inputBudgetAndItems()) {
                    calculateBudget();
                    if (!saveToFile()) {
                        cout << "Warning: Failed to save to file, continuing...\n";
                    }
                    displayResults();
                    break; // Exit after adding budget
                } else {
                    cout << "Program terminated due to invalid input.\n";
                    red;
                    exitProgram();
                    break;
                }
            } else if (choice == '2') {
                if (displayHistory()) {
                    exitProgram();
                    break; // Quit after history
                }
                // Continue loop to show menu
            } else if (choice == '3') {
                exitProgram();
                break;
            } else {
                cout << "Invalid choice. Please enter 1, 2, or 3.\n";
            }
        } while (true);
    }
};

int main()
{
    BudgetPlanner planner;
    planner.run();
    return 0;
}
