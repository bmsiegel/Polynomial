#ifndef _NODE_H_
#define _NODE_H_
/**
 * This is a basic Node class that can used by any singly linked data structure.
 * It has a data item and a pointer to the next Node.
 */ 
template <typename T>
class Node
{
private:
	T data; //this is the data
	Node* next; //this is the pointer to the next Node
public:
	/**
	 * This constructor sets the data to the default value for T and next to nullptr
	 */ 
	Node();
	/**
	 * This uses the parameter to initialize the data and sets next to the nullptr
	 * @param data the data value to store in the data field
	 */ 
	Node( T data );
	/**
	 * This uses the parameters to initialize the data and next pointer
	 * @param data the data value to store in the data field
	 * @param next the value to use for the next pointer
	 */ 
	Node( T data, Node* next );
	/**
	 * This will set the next pointer to the value given in the parameter
	 * @param next the value to use for the next pointer
	 */ 
	void setNext( Node* next );
	/**
	 * This will set the data value to the value given in the parameter
	 * @param data the value to use for the data field
	 */ 
	void setData( T data );
	/**
	 * This will return the next pointer from the Node
	 * @return the value of the next pointer in the Node
	 */ 
	Node* getNext() const;
	/**
	 * This will return the data value from the Node
	 * @return the value of the data in the Node
	 */ 
	T getData() const;
};
#endif
