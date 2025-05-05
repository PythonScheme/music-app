/* Citation and Sources...
Final Project Milestone 5
Module: Billable
Filename: Billable.cpp
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
#include "Billable.h"
#include "Utils.h"

using namespace std;

namespace seneca {
    // Protected methods
    void Billable::price(double value) {
        m_price = value;
    }

    void Billable::name(const char* name) {
        delete[] m_name;
        m_name = ut.alDynCstr(name);
    }

    // Constructor and rule of three implementation
    Billable::Billable() : m_name(nullptr), m_price(0.0) {
    }

    Billable::Billable(const Billable& src) : m_name(nullptr), m_price(0.0) {
        *this = src;
    }

    Billable& Billable::operator=(const Billable& src) {
        if (this != &src) {
            name(src.m_name);
            m_price = src.m_price;
        }
        return *this;
    }

    Billable::~Billable() {
        delete[] m_name;
    }

    // Virtual method implementation
    double Billable::price() const {
        return m_price;
    }

    // Type conversion operator
    Billable::operator const char* () const {
        return m_name;
    }

    // Friend helper functions
    double operator+(double money, const Billable& B) {
        return money + B.price();
    }

    double& operator+=(double& money, const Billable& B) {
        money = money + B;
        return money;
    }
}