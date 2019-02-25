//Polynomial: A class to deal with polynomial functions (add, subtract, multiply, mod, divide)

//I didn't cheat (I neither received nor gave unauthorized assistance on this assignment)

//Programmer: Brady Siegel

#include "Polynomial.hpp"

Polynomial::Polynomial() //Constructor doesn't need to do anything, no terms, no operations
{
}
void Polynomial::insert_term(Term theTerm) //Places term in the linkedlist and bubble sorts by power to put it together. Calls fix_terms to add like powers
{
  terms.insert(1, theTerm);
  sortTerms();
  if (terms.getLength() > 1)
  {
    fix_terms(*this);
  }
}
void Polynomial::sortTerms() //Bubble sort by power
{
  bool go = true;
  while (go)
  {
    go = false;
    for (int c = 1; c < terms.getLength(); c++)
    {
      if (terms.getEntry(c).get_power() < terms.getEntry(c + 1).get_power())
      {
        Term temp = terms.getEntry(c + 1);
        terms.replace(c + 1, terms.getEntry(c));
        terms.replace(c, temp);
        go = true;
      }
    }
  }
}
Polynomial Polynomial::operator+(const Polynomial &rhs) //Adds two polynomials
{
  //Puts all the terms into a singular polynomial, then calls fix_terms to combine like terms and clear_zeroes to clear zero terms
  Polynomial result;
  for (int c = 1; c <= terms.getLength(); c++)
  {
    result.insert_term(Term(terms.getEntry(c).get_coefficient(), terms.getEntry(c).get_power()));
  }
  for (int c = 1; c <= rhs.terms.getLength(); c++)
  {
    result.insert_term(Term(rhs.terms.getEntry(c).get_coefficient(), rhs.terms.getEntry(c).get_power()));
  }
  result.clear_zeroes();
  return fix_terms(result);
}
Polynomial Polynomial::operator*(const Polynomial &rhs) //multiplieis two polynomials
{
  //Takes each term in *this, and for each term in rhs, multiplies the values and puts it in Polynomial P
  Polynomial p;
  for (int c = 1; c <= terms.getLength(); c++)
  {
    LinkedList<Term> rTerms = rhs.terms;
    int lPower = terms.getEntry(c).get_power();
    double lCoeff = terms.getEntry(c).get_coefficient();
    for (int q = 1; q <= rTerms.getLength(); q++)
    {
      int rPower = rhs.terms.getEntry(q).get_power();
      double rCoeff = rhs.terms.getEntry(q).get_coefficient();
      p.insert_term(Term(rCoeff*lCoeff, rPower + lPower));
    }
  }
  return fix_terms(p); //combine like terms
}
Polynomial Polynomial::fix_terms(Polynomial &p) //Function to combine like terms
{
  for (int c = 1; c <= p.terms.getLength(); c++)
  {
    int getPower = p.terms.getEntry(c).get_power();
    double newCoeff = p.terms.getEntry(c).get_coefficient();
    for (int q = 1; q <= p.terms.getLength(); q++)
    {
      if (getPower == p.terms.getEntry(q).get_power() && c != q)
      {
        Term temp2 = p.terms.getEntry(q);
        newCoeff += temp2.get_coefficient(); //Add up any terms that have the same power
        p.terms.remove(q); //remove the extra term that was just added to avoid double counting
      }
      p.terms.replace(c,Term(newCoeff,getPower)); //replace the original term with the new added coefficient and the same power
    }
  }
  p.sortTerms(); //Sort to be certain that the powers are in decending order
  return p;
}
int Polynomial::degree() //returns the degree of the polynomial (highest power)
{
  for (int c = 1; c <= terms.getLength(); c++)
  {
    if (terms.getEntry(c).get_coefficient() != 0) //skips all the zero terms if there are any
    {
      return terms.getEntry(c).get_power();
    }
  }
  return 0;
}
Term Polynomial::degreeTerm() //returns term with highest power
{
  for (int c = 1; c <= terms.getLength(); c++)
  {
    if (terms.getEntry(c).get_coefficient() != 0)
    {
      return terms.getEntry(c);
    }
  }
}
void Polynomial::clear_zeroes() //removes any terms that have a zero coefficient
{
  for (int c = 1; c <= terms.getLength(); c++)
  {
    if (terms.getEntry(c).get_coefficient() == 0)
    {
      terms.remove(c);
      c--; //Go back one to make sure everything is checked
    }
  }
}
void Polynomial::zero_fill(int degree) //Puts zeroes in the polynomial for use with division
{
  while (degree > 0)
  {
    terms.insert(terms.getLength(), Term(0,degree)); //Puts a 0x^power for each number from degree to 0, then combines like terms to fix any double powers
    degree--;
  }
  fix_terms(*this);
}
Polynomial Polynomial::operator-(const Polynomial &rhs) //Multiplies rhs by -1 then adds to *this
{
  Polynomial p;
  Polynomial q;
  q.insert_term(Term(-1,0));
  p = q*rhs;
  return *this + p;
}
bool Polynomial::checkTerms() //Checks for a negative power for division
{
  for (int c = 1; c <= terms.getLength(); c++)
  {
    if (terms.getEntry(c).get_power() < 0)
    {
      return false;
    }
  }
  return true;
}
Polynomial Polynomial::operator/(const Polynomial &rhs) //Divides two polynomials
{
  Polynomial result;
  Polynomial clear;
  Polynomial q = rhs;
  Polynomial n = *this;
  q = rhs;
  if (!q.checkTerms()) //Check for a negative power in divisor
  {
    throw PrecondViolatedExcept("Negative Power with Division/Mod");
  }
  if (q.degree() > n.degree()) //If rhs degree is greater than *this degree it's going to be zero no matter what
  {
    return clear;
  }
  else
  {
    n.zero_fill(n.degree()); //Have all the same terms for dvision
    q.zero_fill(n.degree());
    n.sortTerms(); //Make sure degrees are correct
    q.sortTerms();
    Polynomial d = q; //Need to hold on to q for the algorithm, so passed q to d so it can be changed and used in the modDivideHelper
    while (n.degree() >= q.degree())
    {
      d = q;
      n.modDivideHelper(n, d, result);
    }
    return result;
  }
}
Polynomial Polynomial::operator%(const Polynomial &rhs)
{
  Polynomial result;
  Polynomial q = rhs;
  Polynomial n = *this;
  q = rhs;
  if (!q.checkTerms()) //Check for negative power
  {
    throw PrecondViolatedExcept("Negative Power with Modulus");
  }
  if (q.degree() > n.degree()) //If rhs degree is greater mod is going to return the original *this
  {
    return n;
  }
  n.zero_fill(n.degree());
  q.zero_fill(n.degree());
  n.sortTerms();
  q.sortTerms();
  Polynomial d = q;
  while (n.degree() >= q.degree())
  {
    d = q;
    n.modDivideHelper(n, d, result);
  }
  return n;
}
void Polynomial::modDivideHelper(Polynomial& q, Polynomial& d, Polynomial &result)
{
  //Follows these steps
  //1. Calculate the left shift of the polynomial
  //2. Shift
  //3. Calculate multiplier of the result term (highest power coefficient/highest power coefficient)
  //4. Inserts the term Multiplier*x^shift to a new result polynomial
  //5. Multiply d by multiplier and subtract from *this
  //6. fix_terms
  int shift = q.degree() - d.degree(); //1
  if (shift != 0)
  {
    for (int c = 1; c <= d.terms.getLength() - shift; c++) //2
    {
      d.terms.replace(c, Term(d.terms.getEntry(c + shift).get_coefficient(), d.terms.getEntry(c).get_power()));
      d.terms.replace(c + shift, Term(0, d.terms.getEntry(c + shift).get_power()));
    }

  }
  q.sortTerms();
  double mult = q.degreeTerm().get_coefficient()/d.degreeTerm().get_coefficient(); //3
  result.insert_term(Term(mult, shift)); //4
  Polynomial multiply;
  multiply.insert_term(Term(mult,0)); //5
  d = d*multiply;
  *this = *this - d;
  fix_terms(*this); //6
}
std::ostream& operator<<(std::ostream &out, const Polynomial &rhs)
{
  Polynomial p = rhs;
  p.clear_zeroes(); //Removes any zero terms because they are not necessary for outputs
  if (p.terms.getLength() == 0)
  {
    out << "0";
  }
  for (int c = 1; c <= p.terms.getLength(); c++)
  {
    Term term = p.terms.getEntry(c);
    if (c > 1) //If term is number 1, don't need the plus
    {
      if (term.get_coefficient() > 0) //If greater than zero need to add in the plus sign
      {
        out << "+" << term;
      }
      else
      {
        out << term; //If it's negative the minus is already there
      }
    }
    else
    {
        out << term;
    }
  }
  return out;
}
