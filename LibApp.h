/*
Final Project Milestone 5
Module: LibApp
Filename: LibApp.h
Version 1.0
Author	Kirpal Virk
Student Id 155588213
I have done all the coding by myself and only copied the code
that my professor provided to complete my project milestones.
-----------------------------------------------------------
*/
#ifndef SDDA_LibApp_H_
#define SDDA_LibApp_H_

#include <iostream>

#include "Book.h"
#include "Menu.h"
#include "Publication.h"
#include "PublicationSelector.h"

namespace sdds
{
    class LibApp
    {
        char f_name[256];
        Publication *pubs[SDDS_LIBRARY_CAPACITY];
        bool m_changed = false;
        int nolp;
        int llrn;

        Menu m_mainMenu;
        Menu m_pTypeMenu;
        Menu m_exitMenu;

        bool confirm(const char *message);
        void load();           // prints: "Loading Data"<NEWLINE>
        void save();           // prints: "Saving Data"<NEWLINE>
        int search(const int); // prints: "Searching for publication"<NEWLINE>
        void returnPub();      /*  Calls the search() method.
                                   prints "Returning publication"<NEWLINE>
                                   prints "Publication returned"<NEWLINE>
                                   sets m_changed to true;
                               */
        Publication *getPub(const int libRef) const;
        void newPublication();
        void removePublication();
        void checkOutPub();

    public:
        LibApp(const char *);
        ~LibApp();
        void run();
    };

}
#endif