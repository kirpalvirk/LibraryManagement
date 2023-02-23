/*
Final Project Milestone 5
Module: Publication
Filename: Publication.cpp
Version 1.0
Author	Kirpal Virk
Student Id 155588213
I have done all the coding by myself and only copied the code
that my professor provided to complete my project milestones.
-----------------------------------------------------------
*/
#include "Publication.h"

#include <cstring>
#include <iomanip>
#include <iostream>

#include "Lib.h"
using namespace std;

namespace sdds
{
    Publication::Publication()
    {
        m_title = nullptr;
        m_shelfId[0] = '\0';
        m_membership = 0;
        m_libRef = -1;
        m_date = Date();
    };
    Publication::Publication(const Publication &src)
    {
        m_title = nullptr;
        *this = src;
    };
    Publication &Publication::operator=(const Publication &src)
    {
        if (this != &src)
        {
            strcpy(m_shelfId, src.getShelf());
            m_libRef = src.getRef();
            m_date = src.checkoutDate();
            m_membership = src.getMembership();

            if ((const char *)src)
            {
                delete[] m_title;
                m_title = new char[strlen((const char *)src) + 1];
                strcpy(m_title, (const char *)src);
            }
            else
            {
                delete[] m_title;
                m_title = nullptr;
            }
        }

        return *this;
    }
    void Publication::set(int member_id) { m_membership = member_id; };
    void Publication::setRef(int value) { m_libRef = value; };
    void Publication::resetDate() { m_date = Date(); };
    char Publication::type() const { return 'P'; };
    // Returns the character 'P' to identify this object as a "Publication object"
    bool Publication::onLoan() const { return m_membership != 0; };
    // Returns true is the publication is checkout (membership is non-zero)
    Date Publication::checkoutDate() const { return m_date; };
    // Returns the date attribute
    bool Publication::operator==(const char *title) const
    {
        return strstr(m_title, title);
    };
    // Returns true if the argument title appears anywhere in the title of the
    // publication. Otherwise, it returns false; (use strstr() function in
    // <cstring>)
    Publication::operator const char *() const { return m_title; };
    // Returns the title attribute
    int Publication::getRef() const { return m_libRef; };
    const char *Publication::getShelf() const { return m_shelfId; };
    int Publication::getMembership() const { return m_membership; };
    // Returns the libRef attirbute.
    bool Publication::conIO(ios &io) const
    {
        return &io == &std::cout || &io == &std::cin;
    };

    ostream &Publication::write(ostream &os) const
    {
        if (conIO(os))
        {
            char display[SDDS_TITLE_WIDTH + 1] = {'\0'};
            strncpy(display, m_title, SDDS_TITLE_WIDTH);

            os << "| " << m_shelfId << " | ";
            os << left << setfill('.') << setw(SDDS_TITLE_WIDTH) << display;
            os << " | " << setw(5) << setfill(' ');
            if (m_membership)
            {
                os << m_membership;
            }
            else
            {
                os << " N/A ";
            }
            //  N/A
            os << " | " << m_date << " |";
        }
        else
        {
            // P	2001	P001	The Toronto Star	34037	2021/11/17
            os << type() << "	" << m_libRef << "	" << m_shelfId << "	"
               << m_title << "	" << m_membership << "	" << m_date;
        }

        return os;
    };
    istream &Publication::read(istream &is)
    {
        int libRef = -1;
        int membership = 0;
        char shelf[5] = {'\0'};
        char title[100] = {'\0'};
        Date date;
        if (conIO(is))
        {
            cout << "Shelf No: ";
            is >> shelf;
            if (strlen(shelf) != 4)
            {
                is.setstate(ios::failbit);
                cout << "Title: ";
                cout << "Date: ";
                return is;
            }
            else
            {
                cout << "Title: ";
                is.ignore();
                is.getline(title, 100);
                cout << "Date: ";
                is >> date;
            }
        }
        else
        {
            is >> libRef >> shelf;
            is.ignore();
            is.getline(title, 100, '\t');
            is >> membership >> date;
        }

        // cout << "lf:" << libRef << endl;
        // cout << "sh:" << shelf << endl;
        // cout << "t:" << title << endl;
        // cout << "d:" << date << endl;
        if (date.errCode() == 0)
        {
            delete[] m_title;
            // cout << title << endl;
            m_title = new char[strlen(title) + 1];
            strcpy(m_title, title);

            m_libRef = libRef;
            m_membership = membership;
            strcpy(m_shelfId, shelf);
            m_date = date;
        }
        else
        {
            is.setstate(ios::failbit);
        }

        // cout << "m_t:" << m_title << endl;
        return is;
    };

    Publication::operator bool() const
    {
        return m_title != nullptr && m_shelfId[0] != '\0';
    };

    Publication::~Publication()
    {
        if (m_title != nullptr)
        {
            delete[] m_title;
            m_title = nullptr;
        }
    };

    ostream &operator<<(ostream &os, const Streamable &p)
    {
        if (p)
        {
            return p.write(os);
        }
        return os;
    };
    istream &operator>>(istream &is, Streamable &p) { return p.read(is); };
}