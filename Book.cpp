/*
Final Project Milestone 5
Module: Book
Filename: Book.cpp
Version 1.0
Author	Kirpal Virk
Student Id 155588213
I have done all the coding by myself and only copied the code
that my professor provided to complete my project milestones.
-----------------------------------------------------------
*/
#include "Book.h"

#include <cstring>
#include <iomanip>
#include <iostream>

using namespace std;
namespace sdds
{

    char Book::type() const { return 'B'; };

    Book::Book() { a_name = nullptr; };
    Book::Book(const Book &src) : Publication(src)
    {
        a_name = nullptr;
        *this = src;
    };
    Book::~Book()
    {
        delete[] a_name;
        a_name = nullptr;
    };
    Book &Book::operator=(const Book &src)
    {
        if (this != &src)
        {
            Publication &temp = *this;
            temp = src;

            if (src.a_name)
            {
                if (a_name != nullptr)
                {
                    delete[] a_name;
                    a_name = nullptr;
                }
                a_name = new char[strlen(src.a_name) + 1];
                strcpy(a_name, src.a_name);
            }
            else
            {
                delete[] a_name;
                a_name = nullptr;
            }
        }

        return *this;
    };

    void Book::set(int member_id)
    {
        Publication::set(member_id);
        Publication::resetDate();
    };

    Book::operator bool() const
    {
        return a_name != nullptr && (Publication) * this;
    }

    ostream &Book::write(ostream &os) const
    {
        Publication::write(os);
        if (conIO(os))
        {
            char display[SDDS_AUTHOR_WIDTH + 1] = {'\0'};
            strncpy(display, a_name, SDDS_AUTHOR_WIDTH);

            os << " " << left << setfill(' ') << setw(SDDS_AUTHOR_WIDTH) << display
               << " |";
        }
        else
        {
            os << "\t" << a_name;
        }
        return os;
    };

    istream &Book::read(istream &is)
    {
        Publication::read(is);
        delete[] a_name;
        a_name = nullptr;

        char *temp = new char[100];

        if (conIO(is))
        {
            is.ignore(1, '\n');
            cout << "Author: ";
            is.getline(temp, 100);
        }
        else
        {
            is.ignore(1);
            is.getline(temp, 100, '\n');
            is.putback('\n');
        }

        if (is)
        {
            a_name = new char[strlen(temp) + 1];
            strcpy(a_name, temp);
        }

        delete[] temp;
        temp = nullptr;

        return is;
    }
}