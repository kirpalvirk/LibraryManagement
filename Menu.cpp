/*
Final Project Milestone 5
Module: Menu
Filename: Menu.cpp
Version 1.0
Author	Kirpal Virk
Student Id 155588213
I have done all the coding by myself and only copied the code
that my professor provided to complete my project milestones.
-----------------------------------------------------------
*/

#define _CRT_SECURE_NO_WARNINGS
#include <cstring>
#include <iomanip>
#include <iostream>
using namespace std;
#include "Menu.h"
namespace sdds
{
    MenuItem::MenuItem() { c = nullptr; };
    MenuItem::MenuItem(const char *t)
    {
        c = new char[strlen(t) + 1];
        strcpy(c, t);
    };
    MenuItem::~MenuItem()
    {
        if (c)
        {
            delete[] c;
            c = nullptr;
        }
    };
    MenuItem::operator bool() const { return c != nullptr; };
    MenuItem::operator const char *() const { return c; };
    void MenuItem::display() const
    {
        if (c)
        {
            cout << c;
        }
    };

    Menu::Menu()
    {
        title = new MenuItem();
        numberOfItems = 0;
    };
    Menu::Menu(const char *t)
    {
        title = new MenuItem(t);
        numberOfItems = 0;
    };
    Menu::~Menu()
    {
        delete title;
        title = nullptr;
        for (uint i = 0; i < numberOfItems; i++)
        {
            delete menuItems[i];
            menuItems[i] = nullptr;
        }
        numberOfItems = 0;
    };
    void Menu::displayTitle() const { title->display(); };
    void Menu::setTitle(const char *t)
    {
        delete title;
        title = new MenuItem(t);
    };
    void Menu::displayMenu() const
    {
        title->display();
        if (title->c)
        {
            cout << endl;
        }
        for (uint i = 0; i < numberOfItems; i++)
        {
            cout << setfill(' ') << setw(2) << right << i + 1 << "- ";
            menuItems[i]->display();
            cout << endl;
        }
        cout << " 0- Exit" << endl;
    };
    unsigned int Menu::run() const
    {
        displayMenu();
        unsigned int selection;
        bool valid = true;
        cout << "> ";
        do
        {
            if (!valid)
            {
                cout << "Invalid Selection, try again: ";
            };
            cin >> selection;
            if (cin.fail())
            {
                cin.clear();
                cin.ignore(99999, '\n');
                valid = false;
            }
            else
            {
                valid = selection >= 0 && selection <= numberOfItems;
            }
        } while (!valid);
        return selection;
    };
    unsigned int Menu::operator~() const { return run(); };
    Menu &Menu::operator<<(const char *menuitemConent)
    {
        if (numberOfItems < MAX_MENU_ITEMS)
        {
            menuItems[numberOfItems] = new MenuItem(menuitemConent);
            numberOfItems++;
        }
        return *this;
    };
    Menu::operator int() const { return numberOfItems; };
    Menu::operator unsigned int() const { return numberOfItems; };
    Menu::operator bool() const { return numberOfItems > 0; };
    char *Menu::operator[](int index) const
    {
        return menuItems[index % numberOfItems]->c;
    };

    std::ostream &operator<<(std::ostream &os, const Menu &M)
    {
        M.displayTitle();
        return os;
    };
}