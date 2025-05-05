/* Citation and Sources...
Final Project Milestone 5
Module: Menu
Filename: Menu.cpp
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
#include <cstring>
#include <iomanip>
#include "Menu.h"
#include "Utils.h"

using namespace std;

namespace seneca {
    // MenuItem Implementation

    MenuItem::MenuItem(const char* content, unsigned indentNum, unsigned indentSize, int row)
        : m_indentationNum(indentNum), m_indentationSize(indentSize), m_row(row) {
        // Validate content
        bool valid = content && content[0];

        // Check for content with only spaces
        if (valid) {
            bool hasNonSpace = false;
            for (int i = 0; content[i]; i++) {
                if (content[i] != ' ') {
                    hasNonSpace = true;
                    break;
                }
            }
            valid = hasNonSpace;
        }

        // Validate indentation values
        if (valid && indentNum <= 4 && indentSize <= 4 && (row <= (int)MaximumNumberOfMenuItems || row < 0)) {
            m_content = ut.alDynCstr(content);
        }
    }

    MenuItem::~MenuItem() {
        delete[] m_content;
    }

    MenuItem::operator bool() const {
        return m_content != nullptr;
    }

    ostream& MenuItem::display(ostream& ostr) const {
        if (*this) {
            // Display indentation
            for (unsigned i = 0; i < m_indentationNum; i++) {
                for (unsigned j = 0; j < m_indentationSize; j++) {
                    ostr << ' ';
                }
            }

            // Display row number if non-negative
            if (m_row >= 0) {
                ostr << setw(2) << right << m_row << "- ";
            }

            // Skip spaces at the beginning of content
            const char* contentPtr = m_content;
            while (*contentPtr == ' ') {
                contentPtr++;
            }

            ostr << contentPtr;
        }
        else {
            ostr << "??????????";
        }

        return ostr;
    }

    // Menu Implementation

    Menu::Menu(const char* title, const char* exitOption, unsigned indentNum, unsigned indentSize)
        : m_indentNum(indentNum), m_indentSize(indentSize), m_numMenuItems(0),
        m_title(title, indentNum, indentSize, -1),
        m_exitOption(exitOption, indentNum, indentSize, 0),
        m_selPrompt("> ", indentNum, indentSize, -1) {
    }

    Menu::~Menu() {
        for (unsigned i = 0; i < m_numMenuItems; i++) {
            delete m_menuItems[i];
            m_menuItems[i] = nullptr;
        }
    }

    Menu& Menu::operator<<(const char* menuItem) {
        if (m_numMenuItems < MaximumNumberOfMenuItems) {
            m_menuItems[m_numMenuItems] = new MenuItem(menuItem, m_indentNum, m_indentSize, m_numMenuItems + 1);
            m_numMenuItems++;
        }
        return *this;
    }

    unsigned Menu::select() const {
        // Display title if valid
        if (m_title) {
            m_title.display(cout) << endl;
        }

        // Display menu items
        for (unsigned i = 0; i < m_numMenuItems; i++) {
            m_menuItems[i]->display(cout) << endl;
        }

        // Display exit option
        m_exitOption.display(cout) << endl;

        // Display selection prompt
        m_selPrompt.display(cout);

        // Get valid selection using Utils
        return ut.getInt(0, m_numMenuItems);
    }

    unsigned operator<<(ostream& ostr, const Menu& m) {
        unsigned selection = 0;

        // Only perform selection when ostr is cout
        if (&ostr == &cout) {
            selection = m.select();
        }

        return selection;
    }
}