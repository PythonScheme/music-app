/* Citation and Sources...
Final Project Milestone 5
Module: Food
Filename: Food.h
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

#ifndef SENECA_FOOD_H
#define SENECA_FOOD_H

#include <iostream>
#include "Billable.h"

namespace seneca {
    class Food : public Billable {
        bool m_ordered{ false };
        bool m_child{ false };
        char* m_customize{ nullptr };

    public:
        // Constructors and rule of three
        Food();
        Food(const Food& src);
        Food& operator=(const Food& src);
        virtual ~Food();

        // Override virtual methods from Billable
        virtual std::ostream& print(std::ostream& ostr = std::cout) const override;
        virtual bool order() override;
        virtual bool ordered() const override;
        virtual std::ifstream& read(std::ifstream& file) override;
        virtual double price() const override;
    };
}

#endif // !SENECA_FOOD_H