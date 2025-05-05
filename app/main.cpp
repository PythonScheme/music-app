/* Citation and Sources...
Final Project Milestone 5
Module: main
Filename: main.cpp
Version 1.0
Author: Your Name, Student ID, Email
Revision History
-----------------------------------------------------------
Date      Reason
2024/05/04  Preliminary release
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.
-----------------------------------------------------------*/

#include <iostream>
#include "Menu.h"
#include "Ordering.h"
using namespace std;
using namespace seneca;

int main() {
    // Create Ordering object with food and drink CSV files
    Ordering ord("drinks.csv", "foods.csv");

    // Check if files were loaded successfully
    if (!ord) {
        cout << "Failed to open data files or the data files are corrupted!" << endl;
        return 1; // Exit with error code
    }

    // Create main menu
    Menu mainMenu("Seneca Restaurant", "End Program");

    // Add menu options
    mainMenu << "Order" << "Print Bill" << "Start a New Bill" << "List Foods" << "List Drinks";

    // Sub-menu for ordering
    Menu orderMenu("Order Menu", "Back to main menu", 1);
    orderMenu << "Food" << "Drink";

    // Menu for exit confirmation
    Menu exitConfirmation("You have bills that are not saved. Are you sure you want to exit?", "No");
    exitConfirmation << "Yes";

    // Main program loop
    bool running = true;
    while (running) {
        // Display main menu and get selection
        unsigned int option = mainMenu.select();

        switch (option) {
        case 1: // Order
        {
            unsigned int orderOpt = orderMenu.select();
            switch (orderOpt) {
            case 1: // Food
                ord.orderFood();
                break;
            case 2: // Drink
                ord.orderDrink();
                break;
            }
        }
        break;
        case 2: // Print Bill
            ord.printBill(cout);
            break;
        case 3: // Start a New Bill
            ord.resetBill();
            break;
        case 4: // List Foods
            ord.listFoods();
            break;
        case 5: // List Drinks
            ord.listDrinks();
            break;
        case 0: // Exit
            if (ord.hasUnsavedBill()) {
                // Show confirmation menu if there are unsaved bills
                if (exitConfirmation.select() == 1) {
                    running = false;
                }
            }
            else {
                running = false;
            }
            break;
        }
    }

    return 0;
}