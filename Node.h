#ifndef NODE_H
#define NODE_H


//This defines a Node. It adds functionality for a 'previously used' flag.
//By design, once the flag has been triggered, it cannot be unset.

template <class T>
class Node
{
public:

  //Constructor.
  Node(T value=T(), Node<T>* next=nullptr);

  //Set the value of this Node.
  void setValue(T value);

  //Get the value of this Node.
  T getValue();

  //Set this Node's next pointer.
  void setNext(Node<T>* next);

  //Get the next Node.
  Node<T>* getNext();

private:

  T m_value;          //Value of the Node.
  Node<T>* m_next;    //Pointer to this Node's next Node.

};

#include "Node.hpp"

#endif
