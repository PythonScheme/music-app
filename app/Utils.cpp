/* Citation and Sources...
Final Project Milestone 5
Module: Utils
Filename: Utils.cpp
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
#include "Utils.h"

using namespace std;

namespace seneca {
    // Initialize singleton instance
    Utils ut;

    // Foolproof integer input
    int Utils::getInt() const {
        int value;
        bool validInput = false;
        char newline = '\0';

        while (!validInput) {
            cin >> value;

            if (cin.fail()) {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Invalid integer: ";
            }
            else {
                newline = cin.get();
                if (newline != '\n') {
                    cin.ignore(1000, '\n');
                    cout << "Only an integer please: ";
                }
                else {
                    validInput = true;
                }
            }

            if (cin.eof()) {
                cin.clear();
                cout << "You must enter a value: ";
            }
        }

        return value;
    }

    // Foolproof integer input within range
    int Utils::getInt(int min, int max) const {
        int value;
        bool validInput = false;

        while (!validInput) {
            value = getInt();

            if (value < min || value > max) {
                cout << "Invalid value: [" << min << "<= value <=" << max << "], try again: ";
            }
            else {
                validInput = true;
            }
        }

        return value;
    }

    // Allocate dynamic memory for C-string
    char* Utils::alDynCstr(const char* cstr) const {
        char* newStr = nullptr;

        if (cstr && cstr[0]) {
            newStr = new char[strlen(cstr) + 1];
            strcpy(newStr, cstr);
        }

        return newStr;
    }

    // Generate bill filename
    char* Utils::makeBillFileName(char* filename, size_t billNo) const {
        char billFileName[21] = "bill_";
        size_t temp = billNo;
        int cnt = 5;
        int length;
        // Calculate the number of digits
        do {
            cnt++;
            temp /= 10;
        } while (temp > 0);
        length = cnt;
        // Convert each digit to character from the end
        while (billNo > 0) {
            billFileName[--cnt] = (billNo % 10) + '0';
            billNo /= 10;
        }
        // Handle the case when billNo is 0
        if (billFileName[cnt - 1] == '\0') {
            billFileName[--cnt] = '0';
        }
        // Attach .txt to the end of the file name
        for (int i = 0; ".txt"[i]; i++) {
            billFileName[length++] = ".txt"[i];
        }
        billFileName[length] = '\0';
        strcpy(filename, billFileName);
        return filename;
    }
}