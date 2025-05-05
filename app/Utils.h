/* Citation and Sources...
Final Project Milestone 5
Module: Utils
Filename: Utils.h
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

#ifndef SENECA_UTILS_H
#define SENECA_UTILS_H

#include <iostream>

namespace seneca {
    class Utils {
    public:
        // For handling integer inputs
        int getInt() const;
        int getInt(int min, int max) const;

        // For dynamic memory allocation of C-strings
        char* alDynCstr(const char* cstr) const;

        // For generating bill filenames
        char* makeBillFileName(char* filename, size_t billNo) const;
    };

    // Singleton Utils instance
    extern Utils ut;
}

#endif // !SENECA_UTILS_H