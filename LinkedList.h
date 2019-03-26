#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include "Node.h"

template <typename T>
class LinkedList
{
public:
  //Constructor.
  LinkedList();

  //Destructor.
  ~LinkedList();

  //Removes the node containing the given value from the list.
  bool erase(T value, Node<T>* current=nullptr, Node<T>* prev=nullptr);

  //Adds to the end of the list.
  void insert(T value, Node<T>* current=nullptr);

  //Prints the full contents of this LinkedList in a readable format.
  void print();

  //Search for a given value in this LinkedList. If not found, returns null.
  Node<T>* find(T value);

  //Returns whether this LinkedList is empty.
  bool isEmpty();

  //Determine whether to print the interactions with the hash table
  void setPrintable(bool printable);

  //Return the front Node
  Node<T>* getFront();


private:
  bool PRINTABLE; //If the hash size is <= 25, outputs are enabled.

  Node<T>* m_front; //Pointer to the front of this LinkedList.
  int m_size;       //Size tracking integer, for convenience.


};

#include "LinkedList.hpp"

#endif
