/* Citation and Sources...
Final Project Milestone 5
Module: Billable
Filename: Billable.h
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

#ifndef SENECA_BILLABLE_H
#define SENECA_BILLABLE_H

#include <iostream>
#include <fstream>

namespace seneca {
    class Billable {
        char* m_name{ nullptr };
        double m_price{ 0.0 };

    protected:
        // Setter methods for derived classes
        void price(double value);
        void name(const char* name);

    public:
        // Constructors and rule of three
        Billable();
        Billable(const Billable& src);
        Billable& operator=(const Billable& src);
        virtual ~Billable();

        // Virtual method for price calculation
        virtual double price() const;

        // Pure virtual methods to be implemented by derived classes
        virtual std::ostream& print(std::ostream& ostr = std::cout) const = 0;
        virtual bool order() = 0;
        virtual bool ordered() const = 0;
        virtual std::ifstream& read(std::ifstream& file) = 0;

        // Operator overloads
        operator const char* () const;

        // Friend helper functions
        friend double operator+(double money, const Billable& B);
        friend double& operator+=(double& money, const Billable& B);
    };
}

#endif // !SENECA_BILLABLE_H