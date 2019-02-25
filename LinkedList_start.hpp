//  Created by Frank M. Carrano and Timothy M. Henry.
//  Copyright (c) 2017 Pearson Education, Hoboken, New Jersey.

/** ADT list: Link-based implementation.
    Listing 9-2.
    @file LinkedList.hpp */

#ifndef LINKED_LIST_
#define LINKED_LIST_

#include <utility> //for swap

#include "ListInterface.hpp"
#include "Node.hpp"
#include "PrecondViolatedExcept.h"

/**
 * This is a LinkedList class. It uses Nodes to store data.
 */
template<class T>
class LinkedList : public ListInterface<T>
{
private:
   Node<T>* head; // Pointer to first node in the chain;
                            // (contains the first entry in the list)
   int count;           // Current count of list items

   // Locates a specified node in this linked list.
   // @pre  position is the number of the desired node;
   //       position >= 1 and position <= itemCount.
   // @post  The node is found and a pointer to it is returned.
   // @param position  The number of the node to locate.
   // @return  A pointer to the node at the given position.
   Node<T>* getNodeAt(int position) const;

public:
   LinkedList();
   /**
    * This is the copy constructor. It make a copy of the parameter.  It is also used by the operator= in the copy-swap paradigm.
    * @param rhs - the LinkedList we are copying during construction
    */
   LinkedList(const LinkedList<T>& rhs);
   virtual ~LinkedList();
   /**
    * This is the assignment operator. It uses the copy-swap paradigm to create a copy of the parameter
    * @param rhs - the LinkedList we are assigning to this
    * @return a reference to the list that was copied into, a.k.a. *this
    */
   LinkedList& operator=( LinkedList rhs );

   bool isEmpty() const;
   int getLength() const;
   bool insert(int newPosition, const T& newEntry);
   bool remove(int position);
   void clear();

   /** @throw PrecondViolatedExcept if position < 1 or
                                       position > getLength(). */
   T getEntry(int position) const ;

   /** @throw PrecondViolatedExcept if position < 1 or
                                       position > getLength(). */
   T replace(int position, const T& newEntry);

	/**
	 * This is the swap method. It will swap the internals of the two lists.  Notably it is used in the operator= to implement the copy swap paradigm.  It is also used
	 * by other C++ paradigms.
	 * @param lhs - the LinkedList on the left...Left Hand Side (lhs)
	 * @param rhs - the LinkedList on the right...Right Hand Side (rhs)
	 */
	void swap( LinkedList& lhs, LinkedList& rhs );
}; // end LinkedList

//implement your class here or
//#include your txx or cpp file up to the header...
//not the other way around!
#endif
