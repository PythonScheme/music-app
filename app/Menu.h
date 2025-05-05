/* Citation and Sources...
Final Project Milestone 5
Module: Menu
Filename: Menu.h
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

#ifndef SENECA_MENU_H
#define SENECA_MENU_H

#include <iostream>
#include "constants.h"

namespace seneca {
    // Forward declaration
    class Menu;

    // MenuItem class - fully private and only accessible by Menu
    class MenuItem {
        char* m_content{ nullptr };
        unsigned m_indentationNum{ 0 };
        unsigned m_indentationSize{ 0 };
        int m_row{ -1 };

        // Constructor
        MenuItem(const char* content, unsigned indentNum, unsigned indentSize, int row);

        // Rule of three
        MenuItem(const MenuItem&) = delete;
        MenuItem& operator=(const MenuItem&) = delete;
        ~MenuItem();

        // Type conversion overload
        operator bool() const;

        // Output
        std::ostream& display(std::ostream& ostr) const;

        // Friend declaration
        friend class Menu;
    };

    // Menu class
    class Menu {
        unsigned m_indentNum{ 0 };
        unsigned m_indentSize{ 0 };
        unsigned m_numMenuItems{ 0 };

        MenuItem m_title;
        MenuItem m_exitOption;
        MenuItem m_selPrompt;

        MenuItem* m_menuItems[MaximumNumberOfMenuItems]{};

    public:
        // Constructor
        Menu(const char* title,
            const char* exitOption = "Exit",
            unsigned indentNum = 0,
            unsigned indentSize = 3);

        // Rule of three
        Menu(const Menu&) = delete;
        Menu& operator=(const Menu&) = delete;
        ~Menu();

        // Add MenuItem
        Menu& operator<<(const char* menuItem);

        // Select and Display
        unsigned select() const;

        // Friend helper
        friend unsigned operator<<(std::ostream& ostr, const Menu& m);
    };
}

#endif // !SENECA_MENU_H