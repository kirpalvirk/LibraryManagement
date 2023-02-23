#ifndef SDDS_STREAM_H
#define SDDS_STREAM_H

#include <iostream>

#include "Lib.h"
using namespace std;

namespace sdds {
class Streamable {
 public:
  virtual ostream& write(ostream&) const = 0;
  virtual istream& read(istream&) = 0;
  virtual bool conIO(ios&) const = 0;
  virtual operator bool() const = 0;
  virtual ~Streamable(){};
};
ostream& operator<<(ostream&, const Streamable&);
istream& operator>>(istream&, Streamable&);
}  // namespace sdds

#endif