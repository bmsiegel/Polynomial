//10/1/18: Given by Mr. McPherson

#ifndef NODE_H
#define NODE_H

template <typename T>
class Node
{
private:
  T data;
  Node* next;
public:
  Node() { data = T(); next = nullptr;}
  Node(T data) {this->data = data; next = nullptr;}
  Node(T data, Node *next) {this->data = data; this->next = next;}

  void setNext(Node * next) {this->next = next;}
  void setData(T data) {this->data = data;}

  Node * getNext() const {return next;}
  T getData() const {return data;}
};
#endif
