/* Citation and Sources...
Final Project Milestone 5
Module: Ordering
Filename: Ordering.cpp
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
#include <fstream>
#include <iomanip>
#include "Ordering.h"
#include "Menu.h"
#include "Utils.h"

using namespace std;

namespace seneca {
    // Private utility methods
    void Ordering::billTitlePrint(ostream& ostr) const {
        ostr << "Bill # " << setw(3) << setfill('0') << m_billNo
            << " =============================\n";
    }

    void Ordering::printTotals(ostream& ostr, double total) const {
        double taxAmount = total * Tax;
        double grandTotal = total + taxAmount;

        ostr << setfill(' ')
            << right << setw(23) << "Total:" << setw(12) << fixed << setprecision(2) << total << endl
            << right << setw(23) << "Tax:" << setw(12) << fixed << setprecision(2) << taxAmount << endl
            << right << setw(23) << "Total+Tax:" << setw(12) << fixed << setprecision(2) << grandTotal << endl
            << "========================================\n";
    }

    size_t Ordering::countRecords(const char* file) const {
        ifstream fin(file);
        size_t count = 0;
        char ch;

        while (fin.get(ch)) {
            if (ch == '\n') {
                count++;
            }
        }

        return count;
    }

    // Constructor and destructor
    Ordering::Ordering(const char* drinkFile, const char* foodFile)
        : m_foodCount(0), m_drinkCount(0), m_billableCount(0), m_billNo(1), m_foods(nullptr), m_drinks(nullptr) {

        // Count records in each file
        size_t drinkRecords = countRecords(drinkFile);
        size_t foodRecords = countRecords(foodFile);

        // Open files for reading
        ifstream drinkFin(drinkFile);
        ifstream foodFin(foodFile);

        if (drinkFin && foodFin && drinkRecords > 0 && foodRecords > 0) {
            // Allocate dynamic arrays
            m_drinks = new Drink[drinkRecords];
            m_foods = new Food[foodRecords];

            // Read drink records
            size_t drinksRead = 0;
            for (size_t i = 0; i < drinkRecords && !drinkFin.fail(); i++) {
                if (m_drinks[i].read(drinkFin)) {
                    drinksRead++;
                }
            }

            // Read food records
            size_t foodsRead = 0;
            for (size_t i = 0; i < foodRecords && !foodFin.fail(); i++) {
                if (m_foods[i].read(foodFin)) {
                    foodsRead++;
                }
            }

            // Validate all records were read successfully
            if (drinksRead != drinkRecords || foodsRead != foodRecords) {
                // Revert and set to invalid state
                delete[] m_drinks;
                delete[] m_foods;
                m_drinks = nullptr;
                m_foods = nullptr;
            }
            else {
                // Set counters
                m_drinkCount = drinksRead;
                m_foodCount = foodsRead;
            }
        }
    }

    Ordering::~Ordering() {
        // Delete dynamic arrays
        delete[] m_foods;
        delete[] m_drinks;

        // Delete billable items
        for (size_t i = 0; i < m_billableCount; i++) {
            delete m_billItems[i];
            m_billItems[i] = nullptr;
        }
    }

    // Queries
    Ordering::operator bool() const {
        return m_drinks != nullptr && m_foods != nullptr;
    }

    size_t Ordering::noOfBillItems() const {
        return m_billableCount;
    }

    bool Ordering::hasUnsavedBill() const {
        return m_billableCount > 0;
    }

    // Menu options
    void Ordering::listFoods() const {
        cout << "List Of Avaiable Meals" << endl;
        cout << "========================================" << endl;

        for (size_t i = 0; i < m_foodCount; i++) {
            m_foods[i].print() << endl;
        }

        cout << "========================================" << endl;
    }

    void Ordering::listDrinks() const {
        cout << "List Of Avaiable Drinks" << endl;
        cout << "========================================" << endl;

        for (size_t i = 0; i < m_drinkCount; i++) {
            m_drinks[i].print() << endl;
        }

        cout << "========================================" << endl;
    }

    void Ordering::orderFood() {
        // Create food menu
        Menu foodMenu("Food Menu", "Back to Order", 2);

        // Add food items to menu
        for (size_t i = 0; i < m_foodCount; i++) {
            foodMenu << static_cast<const char*>(m_foods[i]);
        }

        // Get selection
        size_t selection = foodMenu.select();

        if (selection != 0 && selection <= m_foodCount) {
            // Create dynamic copy of selected food
            Food* selectedFood = new Food(m_foods[selection - 1]);

            // Assign to next available spot in bill items
            m_billItems[m_billableCount] = selectedFood;

            // Customize the order
            if (selectedFood->order()) {
                // Order was successful, increment bill item count
                m_billableCount++;
            }
            else {
                // Order was cancelled, delete the food item
                delete selectedFood;
                m_billItems[m_billableCount] = nullptr;
            }
        }
    }

    void Ordering::orderDrink() {
        // Create drink menu
        Menu drinkMenu("Drink Menu", "Back to Order", 2);

        // Add drink items to menu
        for (size_t i = 0; i < m_drinkCount; i++) {
            drinkMenu << static_cast<const char*>(m_drinks[i]);
        }

        // Get selection
        size_t selection = drinkMenu.select();

        if (selection != 0 && selection <= m_drinkCount) {
            // Create dynamic copy of selected drink
            Drink* selectedDrink = new Drink(m_drinks[selection - 1]);

            // Assign to next available spot in bill items
            m_billItems[m_billableCount] = selectedDrink;

            // Customize the order
            if (selectedDrink->order()) {
                // Order was successful, increment bill item count
                m_billableCount++;
            }
            else {
                // Order was cancelled, delete the drink item
                delete selectedDrink;
                m_billItems[m_billableCount] = nullptr;
            }
        }
    }

    ostream& Ordering::printBill(ostream& ostr) const {
        double total = 0.0;

        // Print bill header
        billTitlePrint(ostr);

        // Print each item and add to total
        for (size_t i = 0; i < m_billableCount; i++) {
            m_billItems[i]->print(ostr) << endl;
            total += m_billItems[i]->price();
        }

        // Print totals
        printTotals(ostr, total);

        return ostr;
    }

    void Ordering::resetBill() {
        char filename[50];

        // Generate bill filename
        ut.makeBillFileName(filename, m_billNo);

        // Open file for writing
        ofstream fout(filename);

        // Print bill to file
        printBill(fout);

        // Display message
        cout << "Saved bill number " << m_billNo << endl;
        cout << "Starting bill number " << m_billNo + 1 << endl;

        // Delete all bill items
        for (size_t i = 0; i < m_billableCount; i++) {
            delete m_billItems[i];
            m_billItems[i] = nullptr;
        }

        // Increment bill number and reset bill item count
        m_billNo++;
        m_billableCount = 0;
    }
}