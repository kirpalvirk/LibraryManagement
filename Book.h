/*
Final Project Milestone 5
Module: Book
Filename: Book.h
Version 1.0
Author	Kirpal Virk
Student Id 155588213
I have done all the coding by myself and only copied the code
that my professor provided to complete my project milestones.
-----------------------------------------------------------
*/
#ifndef SDDS_BOOK_H
#define SDDS_BOOK_H

#include <iostream>

#include "Publication.h"

using namespace std;

namespace sdds
{
    class Book : public Publication
    {
        char *a_name;

    public:
        Book();
        Book(const Book &);
        ~Book();
        Book &operator=(const Book &);
        char type() const;
        ostream &write(ostream &) const;
        istream &read(istream &);
        void set(int);
        operator bool() const;
    };
} // namespace sdds

#endif