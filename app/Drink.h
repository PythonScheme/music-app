/* Citation and Sources...
Final Project Milestone 5
Module: Drink
Filename: Drink.h
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

#ifndef SENECA_DRINK_H
#define SENECA_DRINK_H

#include <iostream>
#include "Billable.h"

namespace seneca {
    class Drink : public Billable {
        char m_size{ 0 }; // S, M, L, X

    public:
        // Constructor
        Drink();

        // Override virtual methods from Billable
        virtual std::ostream& print(std::ostream& ostr = std::cout) const override;
        virtual bool order() override;
        virtual bool ordered() const override;
        virtual std::ifstream& read(std::ifstream& file) override;
        virtual double price() const override;
    };
}

#endif // !SENECA_DRINK_H