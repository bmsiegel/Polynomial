#include "Term.hpp"

Term::Term(double coefficient, int power)
{
  this->coefficient = coefficient;
  this->power = power;
}
double Term::get_coefficient() const
{
  return coefficient;
}
int Term::get_power() const
{
  return power;
}
std::ostream& operator<< (std::ostream &out, const Term &t)
{
  if (t.coefficient == 0) //Don't print zeroes
  {
    return out;
  }
  else if (t.coefficient == 1) //1x^3 is redundant, but if the power is zero you need it
  {
    if (t.power == 0)
    {
      out << t.coefficient;
    }
    else if (t.power == 1)
    {
      out << "x";
    }
    else
    {
      out << "x^" << t.power;
    }
  }
  else if (t.coefficient == -1) //1 and -1 have different outputs, so I split them up
  {
    if (t.power == 0)
    {
      out << t.coefficient;
    }
    else if (t.power == 1)
    {
      out << "-x";
    }
    else
    {
      out << "-x^" << t.power;
    }
  }
  else //Anything else
  {
    if (t.power == 0)
    {
      out << t.coefficient;
    }
    else if (t.power == 1)
    {
      out << t.coefficient << "x";
    }
    else
    {
      out << t.coefficient << "x^" << t.power;
    }
  }
  return out;
}
