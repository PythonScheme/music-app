/* Citation and Sources...
Final Project Milestone 5
Module: Food
Filename: Food.cpp
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
#include <cstring>
#include "Food.h"
#include "Menu.h"
#include "Utils.h"

using namespace std;

namespace seneca {
    // Constructors and rule of three
    Food::Food() : m_ordered(false), m_child(false), m_customize(nullptr) {
    }

    Food::Food(const Food& src) : Billable(src), m_ordered(false), m_child(false), m_customize(nullptr) {
        *this = src;
    }

    Food& Food::operator=(const Food& src) {
        if (this != &src) {
            Billable::operator=(src);
            m_ordered = src.m_ordered;
            m_child = src.m_child;

            delete[] m_customize;
            m_customize = ut.alDynCstr(src.m_customize);
        }
        return *this;
    }

    Food::~Food() {
        delete[] m_customize;
    }

    // Override virtual methods from Billable
    ostream& Food::print(ostream& ostr) const {
        // Print name (left-justified in 28 spaces, padded with dots)
        ostr << left << setw(28) << setfill('.') << static_cast<const char*>(*this);

        // Print portion type (Child/Adult or .....)
        if (ordered()) {
            ostr << (m_child ? "Child" : "Adult");
        }
        else {
            ostr << ".....";
        }

        // Print price (right-justified in 7 spaces, 2 decimal places)
        ostr << right << setw(7) << setfill(' ') << fixed << setprecision(2) << price();

        // Print customization if it exists and output is to cout
        if (m_customize && &ostr == &cout) {
            ostr << " >> ";

            // Print up to 30 characters of customization
            int maxLen = 30;
            for (int i = 0; m_customize[i] && i < maxLen; i++) {
                ostr << m_customize[i];
            }
        }

        return ostr;
    }

    bool Food::order() {
        // Create menu for food portion selection
        Menu portionMenu("Food Size Selection", "Back", 3);
        portionMenu << "Adult" << "Child";

        // Get selection
        unsigned selection = portionMenu.select();

        if (selection != 0) {
            m_ordered = true;
            m_child = (selection == 2); // Child if selection is 2

            // Prompt for customization
            cout << "Special instructions" << endl;
            cout << "> ";

            // Clear previous customization
            delete[] m_customize;
            m_customize = nullptr;

            // Get customization input
            char temp[1000] = { 0 };
            cin.getline(temp, 1000);

            // If user entered customization, store it
            if (temp[0]) {
                m_customize = ut.alDynCstr(temp);
            }

            return true;
        }
        else {
            // User selected "Back"
            m_ordered = false;
            delete[] m_customize;
            m_customize = nullptr;
            return false;
        }
    }

    bool Food::ordered() const {
        return m_ordered;
    }

    ifstream& Food::read(ifstream& file) {
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

            // Reset other attributes
            m_ordered = false;
            m_child = false;

            delete[] m_customize;
            m_customize = nullptr;
        }

        return file;
    }

    double Food::price() const {
        if (ordered() && m_child) {
            return Billable::price() / 2.0; // Half price for child portion
        }
        return Billable::price();
    }
}