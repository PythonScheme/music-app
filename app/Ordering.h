/* Citation and Sources...
Final Project Milestone 5
Module: Ordering
Filename: Ordering.h
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

#ifndef SENECA_ORDERING_H
#define SENECA_ORDERING_H

#include <iostream>
#include "Billable.h"
#include "Food.h"
#include "Drink.h"
#include "constants.h"

namespace seneca {
    class Ordering {
        // Counters
        size_t m_foodCount{ 0 };
        size_t m_drinkCount{ 0 };
        size_t m_billableCount{ 0 };

        // Bill number
        size_t m_billNo{ 1 };

        // Dynamic arrays
        Food* m_foods{ nullptr };
        Drink* m_drinks{ nullptr };

        // Array of billable items for the current bill
        Billable* m_billItems[MaximumNumberOfBillItems]{};

        // Private utility methods
        void billTitlePrint(std::ostream& ostr) const;
        void printTotals(std::ostream& ostr, double total) const;
        size_t countRecords(const char* file) const;

    public:
        // Constructor and destructor
        Ordering(const char* drinkFile, const char* foodFile);
        ~Ordering();

        // Queries
        operator bool() const;
        size_t noOfBillItems() const;
        bool hasUnsavedBill() const;

        // Menu options
        void listFoods() const;
        void listDrinks() const;
        void orderFood();
        void orderDrink();
        std::ostream& printBill(std::ostream& ostr) const;
        void resetBill();
    };
}

#endif // !SENECA_ORDERING_H