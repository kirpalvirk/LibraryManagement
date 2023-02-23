/*
Final Project Milestone 5
Module: Publication
Filename: Publication.h
Version 1.0
Author	Kirpal Virk
Student Id 155588213
I have done all the coding by myself and only copied the code
that my professor provided to complete my project milestones.
-----------------------------------------------------------
*/
#ifndef SDDS_PUBLICATION_H
#define SDDS_PUBLICATION_H

#include <iostream>

#include "Date.h"
#include "Lib.h"
#include "Streamable.h"

using namespace std;

namespace sdds {
class Publication : public Streamable {
  char* m_title;
  char m_shelfId[SDDS_SHELF_ID_LEN + 1];
  int m_membership;
  int m_libRef;
  Date m_date;

 public:
  Publication();
  ~Publication();
  Publication(const Publication&);
  virtual void set(int member_id);
  void setRef(int value);
  void resetDate();
  virtual char type() const;
  // Returns the character 'P' to identify this object as a "Publication
  // object"
  bool onLoan() const;
  // Returns true is the publication is checkout (membership is non-zero)
  Date checkoutDate() const;
  // Returns the date attribute
  bool operator==(const char* title) const;
  // Returns true if the argument title appears anywhere in the title of the
  // publication. Otherwise, it returns false; (use strstr() function in
  // <cstring>)
  operator const char*() const;
  // Returns the title attribute
  int getRef() const;
  const char* getShelf() const;
  int getMembership() const;
  // Returns the libRef attirbute.
  Publication& operator=(const Publication&);
  ostream& write(ostream&) const;
  istream& read(istream&);
  bool conIO(ios&) const;
  operator bool() const;
};
}  // namespace sdds

#endif