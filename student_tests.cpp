#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "Polynomial.hpp"

TEST_CASE("Tests add")
{
  std::stringstream ss1;
  Polynomial p;
  Polynomial q;
  p.insert_term(Term(2,3));
  p.insert_term(Term(2,2));
  p.insert_term(Term(2,1));
  q.insert_term(Term(1,3));
  q.insert_term(Term(3,2));
  q.insert_term(Term(5,1));
  q.insert_term(Term(6,0));
  ss1 << p + q;
  REQUIRE(ss1.str() == "3x^3+5x^2+7x+6");
}
TEST_CASE("Tests subtract")
{
  std::stringstream ss1;
  Polynomial p;
  Polynomial q;
  p.insert_term(Term(2,3));
  p.insert_term(Term(2,2));
  p.insert_term(Term(2,1));
  q.insert_term(Term(1,3));
  q.insert_term(Term(3,2));
  q.insert_term(Term(5,1));
  q.insert_term(Term(6,0));
  ss1 << p - q;
  REQUIRE(ss1.str() == "x^3-x^2-3x-6");
}
TEST_CASE("Tests multiply")
{
  std::stringstream ss1;
  Polynomial p;
  Polynomial q;
  p.insert_term(Term(2,1));
  p.insert_term(Term(4,0));
  ss1 << p*p;
  REQUIRE(ss1.str() == "4x^2+16x+16");
}
TEST_CASE("Tests divide")
{
  std::stringstream ss1;
  Polynomial p;
  Polynomial q;
  p.insert_term(Term(1,4));
  p.insert_term(Term(8,3));
  p.insert_term(Term(4,2));
  q.insert_term(Term(1,2));
  q.insert_term(Term(2,1));
  q.insert_term(Term(1,0));
  ss1 << p / q;
  REQUIRE(ss1.str() == "x^2+6x-9");
}
TEST_CASE("Tests modulus")
{
  std::stringstream ss1;
  Polynomial p;
  Polynomial q;
  p.insert_term(Term(1,4));
  p.insert_term(Term(8,3));
  p.insert_term(Term(4,2));
  q.insert_term(Term(1,2));
  q.insert_term(Term(2,1));
  q.insert_term(Term(1,0));
  ss1 << p % q;
  REQUIRE(ss1.str() == "12x+9");
}
TEST_CASE("Tests weird stuff")
{
  std::stringstream ss1;
  std::stringstream ss2;
  Polynomial p;
  Polynomial q;
  p.insert_term(Term(1,4));
  p.insert_term(Term(8,3));
  p.insert_term(Term(4,2));
  q.insert_term(Term(1,-2));
  q.insert_term(Term(2,1));
  q.insert_term(Term(1,0));
  REQUIRE_THROWS(p/q);
  REQUIRE_THROWS(p%q);
  Polynomial h;
  Polynomial y;
  h.insert_term(Term(1,2));
  h.insert_term(Term(8,1));
  h.insert_term(Term(4,0));
  y.insert_term(Term(1,1));
  y.insert_term(Term(2,0));
  y.insert_term(Term(1,0));
  ss1 << y / h;
  ss2 << y % h;
  REQUIRE(ss1.str() == "0");
  REQUIRE(ss2.str() == "x+3");
}
