#include "Term.hpp"
#include "LinkedList.hpp"

#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

class Polynomial
{
private:
  LinkedList<Term> terms;
  Polynomial fix_terms(Polynomial &p);
  void sortTerms();
  void zero_fill(int degree);
  void clear_zeroes();
  Term degreeTerm();
  void modDivideHelper(Polynomial& q, Polynomial& d, Polynomial &result);
  bool checkTerms();
  int degree();
public:
  Polynomial();
  void insert_term(Term theTerm);
  Polynomial operator+(const Polynomial &rhs);
  Polynomial operator*(const Polynomial &rhs);
  Polynomial operator-(const Polynomial &rhs);
  Polynomial operator/(const Polynomial &rhs);
  Polynomial operator%(const Polynomial &rhs);
  friend std::ostream& operator<<(std::ostream &out, const Polynomial &rhs);
};

#endif
