//  Created by Frank M. Carrano and Timothy M. Henry.
//  Copyright (c) 2017 Pearson Education, Hoboken, New Jersey.

/** Listing 7-5.
    @file PrecondViolatedExcept.h */

#ifndef PRECOND_VIOLATED_EXCEPT_
#define PRECOND_VIOLATED_EXCEPT_

#include <stdexcept>
#include <string>
/**
 * An exception classed used by the LinkedList to throw when a precondition is not met.
 */ 
class PrecondViolatedExcept : public std::logic_error
{
public:
   /**
    * Constructor for the class
    * @param message the message to send to the exception
    */ 
   PrecondViolatedExcept(const std::string& message = "");
}; // end PrecondViolatedExcept
#endif
