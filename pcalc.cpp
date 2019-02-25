#include "Polynomial.hpp"
#include <fstream>
#include <sstream>

void readPoly(Polynomial &p, Polynomial &q, std::stringstream &ss1, std::stringstream &ss2); //Read in polynomials
bool operate(Polynomial p, Polynomial q, std::string sign, std::ostream &out); //Do calculations

int main(int argc, char* argv[])
{
  if (argc == 2) //Executable and input file
  {
    std::ifstream in(argv[1]);
    std::string poly1;
    std::string poly2;
    std::string sign;
    //Prime test process reprime
    getline(in, poly1, ' ');
    getline(in, sign, ' ');
    getline(in, poly2, '\n');
    while (!in.fail())
    {
      Polynomial p;
      Polynomial q;
      std::stringstream ss1(poly1); //Like ifstream but for a string
      std::stringstream ss2(poly2);
      readPoly(p,q,ss1,ss2);
      if (!operate(p,q,sign,std::cout))
      {
        return EXIT_FAILURE;
      }
      getline(in, poly1, ' ');
      getline(in, sign, ' ');
      getline(in, poly2, '\n');
    }
  }
  else if (argc == 3) //Executable input output file
  {
    std::ifstream in(argv[1]);
    std::ofstream out(argv[2]);
    std::string poly1;
    std::string poly2;
    std::string sign;
    getline(in, poly1, ' ');
    getline(in, sign, ' ');
    getline(in, poly2, '\n');
    while (!in.fail())
    {
      Polynomial p;
      Polynomial q;
      std::stringstream ss1(poly1);
      std::stringstream ss2(poly2);
      readPoly(p,q,ss1,ss2);
      if (!operate(p,q,sign,out))
      {
        return EXIT_FAILURE;
      }
      getline(in, poly1, ' ');
      getline(in, sign, ' ');
      getline(in, poly2, '\n');
    }
  }
  else if (argc == 4) //Executable poly1 sign poly2
  {
    std::string poly1 = argv[1];
    std::string poly2 = argv[3];
    std::string sign = argv[2];
    Polynomial p;
    Polynomial q;
    std::stringstream ss1(poly1);
    std::stringstream ss2(poly2);
    readPoly(p,q,ss1,ss2);
    if (!operate(p,q,sign,std::cout))
    {
      return EXIT_FAILURE;
    }
  }
  else
  {
    std::cout << "Error: Too Many Arguments";
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
void readPoly(Polynomial &p, Polynomial &q, std::stringstream &ss1, std::stringstream &ss2)
{
  std::string term;
  std::string power;
  getline(ss1, term, ',');
  getline(ss1, power, ',');
  while (!ss1.fail())
  {
    p.insert_term(Term(stod(term), stoi(power)));
    getline(ss1, term, ',');
    getline(ss1, power, ',');
  }
  term = "";
  power = "";
  getline(ss2, term, ',');
  getline(ss2, power, ',');
  while (!ss2.fail())
  {
    q.insert_term(Term(stod(term), stoi(power)));
    getline(ss2, term, ',');
    getline(ss2, power, ',');
  }
}
bool operate(Polynomial p, Polynomial q, std::string sign, std::ostream &out) //Does specified calculation, will return false if exeception is thrown
{
  if (sign == "+")
  {
    out << p << " " << sign << " " << q << " = ";
    out << p + q << '\n';
  }
  else if (sign == "-")
  {
    out << p << " " << sign << " " << q << " = ";
    out << p - q << '\n';
  }
  else if (sign == "*")
  {
    out << p << " " << sign << " " << q << " = ";
    out << p * q << '\n';
  }
  else if (sign == "/")
  {
    out << p << " " << sign << " " << q << " = ";
    try
    {
      out << p / q << '\n';
    }
    catch (PrecondViolatedExcept e)
    {
      out << "\nError: Negative Power in Division";
      return false;
    }
  }
  else if (sign == "%")
  {
    out << p << " " << sign << " " << q << " = ";
    try
    {
      out << p % q << '\n';
    }
    catch (PrecondViolatedExcept e)
    {
      out << "\nError: Negative Power in Modulus";
      return false;
    }
  }
  return true;
}
