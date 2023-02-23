/*
Final Project Milestone 5
Module: Menu
Filename: Menu.h
Version 1.0
Author	Kirpal Virk
Student Id 155588213
I have done all the coding by myself and only copied the code
that my professor provided to complete my project milestones.
-----------------------------------------------------------
*/
#ifndef SDDS_MENU_H__
#define SDDS_MENU_H__
#include <iostream>
namespace sdds
{

    const int MAX_MENU_ITEMS = 20;
    class MenuItem
    {
        char *c;
        friend class Menu;
        MenuItem();
        MenuItem(const char *c);
        ~MenuItem();
        operator bool() const;
        operator const char *() const;
        void display() const;
        MenuItem(const MenuItem &) = delete;
        MenuItem &operator=(const MenuItem &) = delete;
    };
    class Menu
    {
        MenuItem *title;
        MenuItem *menuItems[MAX_MENU_ITEMS];
        unsigned int numberOfItems;

    public:
        Menu();
        Menu(const char *);
        Menu(const Menu &) = delete;
        Menu &operator=(const Menu &) = delete;
        ~Menu();
        void displayTitle() const;
        void displayMenu() const;
        void setTitle(const char *);
        unsigned int run() const;
        unsigned int operator~() const;
        Menu &operator<<(const char *);
        operator int() const;
        operator unsigned int() const;
        operator bool() const;
        char *operator[](int index) const;
    };

    std::ostream &operator<<(std::ostream &os, const Menu &M);

}; // namespace sdds

#endif