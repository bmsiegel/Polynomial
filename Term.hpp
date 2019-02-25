#include <iostream>

#ifndef TERM_H
#define TERM_H

class Term
{
private:
  double coefficient;
  int power;
public:
  Term(double coefficient = 0, int power = 0);
  double get_coefficient() const;
  int get_power() const;
  friend std::ostream& operator<< (std::ostream &out, const Term &t);
};

#endif
