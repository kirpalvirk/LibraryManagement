/*
Final Project Milestone 5
Module: LibApp
Filename: LibApp.cpp
Version 1.0
Author	Kirpal Virk
Student Id 155588213
I have done all the coding by myself and only copied the code
that my professor provided to complete my project milestones.
-----------------------------------------------------------
*/

#include "LibApp.h"

#include <cstring>
#include <fstream>
#include <iomanip>
#include <iostream>

using namespace std;
namespace sdds {
bool LibApp::confirm(const char* message) {
  Menu t(message);
  t << "Yes";
  return t.run() == 1;
};
void LibApp::load() {
  cout << "Loading Data" << endl;
  ifstream infile(f_name);
  char type{};
  int i;
  for (i = 0; infile; i++) {
    infile >> type;
    infile.ignore();
    if (infile) {
      if (type == 'P')
        pubs[i] = new Publication;
      else if (type == 'B')
        pubs[i] = new Book;
      if (pubs[i]) {
        infile >> *pubs[i];
        nolp++;
      }
    }
  }
  // cout << i << endl;
  llrn = pubs[nolp - 1]->getRef();
};
void LibApp::save() {
  cout << "Saving Data" << endl;
  ofstream outfile(f_name);
  for (int i = 0; i < nolp; i++) {
    if (pubs[i]->getRef() == 0) {
      continue;
    }
    outfile << *pubs[i] << endl;
  }
}

int LibApp::search(const int mode = 1) {
  // cout << "Searching for publication" << endl;
  int selectType = m_pTypeMenu.run();

  if (selectType == 0) {
    cout << "Aborted!" << endl;
    // cout << endl;
    return 0;
  }

  char type = selectType == 1 ? 'B' : 'P';

  char title[SDDS_TITLE_WIDTH] = {'\0'};
  PublicationSelector pSelector("Select one of the following found matches:");
  cout << "Publication Title: ";
  cin.ignore();
  cin.getline(title, SDDS_TITLE_WIDTH);


  int match = 0;
  // if (title[0] != '\0') {
  for (int i = 0; i < nolp; i++) {
    if (*pubs[i] == title && pubs[i]->getRef() != 0 &&
        type == pubs[i]->type()) {
      if (mode == 2) {
        if (pubs[i]->onLoan()) {
          pSelector << pubs[i];
          match++;
        };
      } else if (mode == 3) {
        if (!pubs[i]->onLoan()) {
          pSelector << pubs[i];
          match++;
        };
      } else {
        pSelector << pubs[i];
        match++;
      }
    }
  }
  // }

  if (match == 0) {
    cout << "No matches found!" << endl;
    return 0;
  }

  pSelector.sort();
  int refVal = pSelector.run();
  if (!refVal) {
    cout << "Aborted!" << endl;
    return 0;
  }

  return refVal;
};

Publication* LibApp::getPub(const int libRef) const {
  for (int i = 0; i < nolp; i++) {
    if (pubs[i]->getRef() == libRef) {
      return pubs[i];
    }
  }

  return nullptr;
};

void LibApp::returnPub() {
  cout << "Return publication to the library" << endl;
  int retVal = search(2);

  if (retVal > 0) {
    Publication* pub = getPub(retVal);
    cout << *pub << endl;
  }

  if (retVal > 0 && confirm("Return Publication?")) {
    Date today = Date();
    Publication* pub = getPub(retVal);
    int duration = today - pub->checkoutDate();
    if (duration > 15) {
      int penalty = duration - 15;
      cout << "Please pay $" << fixed << setprecision(2) << penalty * 0.5;
      cout << " penalty for being " << penalty << " days late!" << endl;
    }
    pub->set(0);
    m_changed = true;
    cout << "Publication returned" << endl;
  }
  cout << endl;
};

void LibApp::newPublication() {
  if (nolp == SDDS_LIBRARY_CAPACITY) {
    cout << "Library is at its maximum capacity!" << endl;
    cout << endl;
    return;
  }

  cout << "Adding new publication to the library" << endl;

  int selectType = m_pTypeMenu.run();

  if (selectType == 0) {
    cout << "Aborted!" << endl;
    cout << endl;
    return;
  }

  Publication* newPub = nullptr;
  if (selectType == 2) {
    newPub = new Publication;
  } else {
    newPub = new Book;
  }

  cin >> *newPub;

  if (cin && confirm("Add this publication to the library?")) {
    if (newPub) {
      llrn++;
      pubs[nolp] = newPub;
      pubs[nolp]->setRef(llrn);
      nolp++;
      m_changed = true;
      cout << "Publication added" << endl;
    } else {
      cout << "Failed to add publication!" << endl;
      delete newPub;
      newPub = nullptr;
    }
  } else {
    delete newPub;
    newPub = nullptr;
    cout << "Aborted!" << endl;
    cout << endl;
    return;
  }
  cout << endl;
};

void LibApp::removePublication() {
  cout << "Removing publication from the library" << endl;
  int refVal = search();
  if (refVal > 0) {
    Publication* pub = getPub(refVal);
    cout << *pub << endl;
  }

  if (refVal > 0) {
    Publication* pub = getPub(refVal);
    //cout << *pub << endl;
    if (confirm("Remove this publication from the library?")) {
      pub->setRef(0);
      m_changed = true;
      cout << "Publication removed" << endl;
    }
  }
  cout << endl;
};
void LibApp::checkOutPub() {
  cout << "Checkout publication from the library" << endl;
  int refVal = search(3);
  int m_number;
  if (refVal > 0) {
    Publication* pub = getPub(refVal);
    cout << *pub << endl;
  }
  if (refVal > 0 && confirm("Check out publication?")) {
    cout << "Enter Membership number: ";
    cin >> m_number;
    while (!m_number || !cin || m_number < 10000 || m_number > 99999) {
      cin.clear();
      cin.ignore(100, '\n');
      cout << "Invalid membership number, try again: ";
      cin >> m_number;
    }
    Publication* pub = getPub(refVal);
    pub->set(m_number);
    pub->resetDate();

    m_changed = true;
    cout << "Publication checked out" << endl;
  }
  cout << endl;
};

LibApp::LibApp(const char* res) {
  strcpy(f_name, res);

  m_mainMenu.setTitle("Seneca Library Application");
  m_mainMenu << "Add New Publication";
  m_mainMenu << "Remove Publication";
  m_mainMenu << "Checkout publication from library";
  m_mainMenu << "Return publication to library";

  m_exitMenu.setTitle(
      "Changes have been made to the data, what would "
      "you like to do?");
  m_exitMenu << "Save changes and exit";
  m_exitMenu << "Cancel and go back to the main menu";

  m_pTypeMenu.setTitle("Choose the type of publication:");
  m_pTypeMenu << "Book";
  m_pTypeMenu << "Publication";

  m_changed = false;
  nolp = 0;
  llrn = 0;

  load();
}

LibApp::~LibApp() {
  for (int i = 0; i < nolp; i++) {
    delete pubs[i];
    pubs[i] = nullptr;
  }
}

void LibApp::run() {
  bool end = false;
  int selection;
  int exit_m = false;
  while (!end) {
    if (exit_m) {
      selection = m_exitMenu.run();
      switch (selection) {
        case 1:
          save();
          end = true;
          break;
        case 2:
          exit_m = false;
          cout << endl;
          break;
        default:
          exit_m = false;
          end = confirm("This will discard all the changes are you sure?");
          break;
      }
    } else {
      selection = m_mainMenu.run();
      switch (selection) {
        case 1:
          newPublication();
          break;
        case 2:
          removePublication();
          break;
        case 3:
          checkOutPub();
          break;
        case 4:
          returnPub();
          break;
        default:
          end = !m_changed;
          exit_m = true;
          break;
      }
    }
  }

  cout << endl << "-------------------------------------------" << endl;
  cout << "Thanks for using Seneca Library Application" << endl;
};
}
