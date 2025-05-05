/* Citation and Sources...
Final Project Milestone 5
Module: Drink
Filename: Drink.cpp
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
#include <iomanip>
#include "Drink.h"
#include "Menu.h"
#include "Utils.h"

using namespace std;

namespace seneca {
    // Constructor
    Drink::Drink() : m_size(0) {
    }

    // Override virtual methods from Billable
    ostream& Drink::print(ostream& ostr) const {
        // Print name (left-justified in 28 spaces, padded with dots)
        ostr << left << setw(28) << setfill('.') << static_cast<const char*>(*this);

        // Print size based on m_size
        if (ordered()) {
            if (m_size == 'S') {
                ostr << "SML..";
            }
            else if (m_size == 'M') {
                ostr << "MID..";
            }
            else if (m_size == 'L') {
                ostr << "LRG..";
            }
            else if (m_size == 'X') {
                ostr << "XLR..";
            }
        }
        else {
            ostr << ".....";
        }

        // Print price (right-justified in 7 spaces, 2 decimal places)
        ostr << right << setw(7) << setfill(' ') << fixed << setprecision(2) << price();

        return ostr;
    }

    bool Drink::order() {
        // Create menu for drink size selection
        Menu sizeMenu("Drink Size Selection", "Back", 3);
        sizeMenu << "Small" << "Medium" << "Large" << "Extra Large";

        // Get selection
        unsigned selection = sizeMenu.select();

        if (selection != 0) {
            // Set size based on selection
            switch (selection) {
            case 1: m_size = 'S'; break; // Small
            case 2: m_size = 'M'; break; // Medium
            case 3: m_size = 'L'; break; // Large
            case 4: m_size = 'X'; break; // Extra Large
            }
            return true;
        }
        else {
            // User selected "Back"
            m_size = 0;
            return false;
        }
    }

    bool Drink::ordered() const {
        return m_size != 0;
    }

    ifstream& Drink::read(ifstream& file) {
        char name[256] = { 0 };
        double price = 0.0;

        // Read the name up to comma
        file.getline(name, 256, ',');

        // Read the price
        file >> price;

        // Skip newline
        file.ignore();

        if (!file.fail()) {
            // Set the name and price
            this->name(name);
            this->price(price);

            // Reset the size to default
            m_size = 0;
        }

        return file;
    }

    double Drink::price() const {
        if (!ordered()) {
            return Billable::price();
        }

        // Adjust price based on size
        switch (m_size) {
        case 'S': return Billable::price() / 2.0;     // Small = half price
        case 'M': return Billable::price() * 3.0 / 4.0; // Medium = 3/4 price
        case 'L': return Billable::price();           // Large = original price
        case 'X': return Billable::price() * 1.5;     // Extra Large = 1.5x price
        default:  return Billable::price();
        }
    }
}