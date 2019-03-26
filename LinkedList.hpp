#include <iostream>

#include "Node.h"
#include "LinkedList.h"

/* NOTE This LinkedList implementation has been slightly modified for use with
        Hash.h. Modifications:
         - insert() method inserts to the front of the list instead of end.
         - All occurances of 'list' in I/O have been replaced with table.
*/

//Constructor
template <class T>
LinkedList<T>::LinkedList()
{
  m_size = 0;
  m_front = nullptr;
}

//Destructor
template <class T>
LinkedList<T>::~LinkedList()
{
  while (!isEmpty()) erase(m_front->getValue());
}

//Erases the node containing the given value from this LinkedList.
template <class T>
bool LinkedList<T>::erase(T value, Node<T>* current, Node<T>* prev)
{
  //Validation Logic
  // if (isEmpty()) {if (PRINTABLE) std::cout << "\nError: " << value << " not in table."; return false; }
  if (current == nullptr) {
    if (prev == nullptr) current = m_front; //Designed such that when both are nullptr, we're at the beginning, and...
    // else { if (PRINTABLE) std::cout << "\nError: " << value << " not in table."; return false; }                   //when current is nullptr but prev is not, we're at the end AND the Value was never found
  }

  //Evaluate the Node
  if (current->getValue() == value) { //Found the value, now remove it.
    if (current == m_front) m_front = m_front->getNext();  //Edge case: Adjust front pointer if removing first value.
    if (prev != nullptr) prev->setNext(current->getNext()); //Re-link if needed
    m_size--;
    delete current;
    // if (PRINTABLE) std::cout << "\n" << value << " removed from table.";
    return true;
  } else { //Keep searching
    return erase(value, current->getNext(), current);
  }
}

//Adds a node to the FRONT of this LinkedList. Abort upon detection of a duplicate value.
template <class T>
void LinkedList<T>::insert(T value, Node<T>* current)
{
  if (isEmpty()) {   //Validate existence of front Node.
    Node<T>* newNode = new Node<T>(value);
    m_front = newNode;
    m_size++;
    return;
  }
  if (current == nullptr) current = m_front; //Designed so this only occurs at entry of recursion. Allows usage of default parameter.
  if (current->getValue() == value) { //Disallow duplicates
    // if (PRINTABLE) std::cout << "\nError: " << value << " already exists in table.";
    return;
  }
  if (current->getNext() != nullptr) insert(value, current->getNext()); //Recurse to end
  else {  //Time to insert - Create a new node and pin it to the FRONT.
    Node<T>* newNode = new Node<T>(value);
    newNode->setNext(m_front); //Pin to front
    m_front = newNode; //Update pointer to front
    m_size++;
    // if (PRINTABLE) std::cout << "\n" << value << " added to table.";
  }
}

template <class T>
void LinkedList<T>::print()
{
  // if (isEmpty()) if (PRINTABLE) std::cout << "(Empty)";
  Node<T>* current = m_front;
  while (current != nullptr) {
    if (PRINTABLE) std::cout << current->getValue() << " ";
    current = current->getNext();
  }
}

template <class T>
Node<T>* LinkedList<T>::find(T value)
{
    Node<T>* current = m_front;

    while (current != nullptr)
      if (current->getValue() == value) return current;
      else current = current->getNext();

    return nullptr;
}

//Returns whether this LinkedList is empty.
template <class T>
bool LinkedList<T>::isEmpty()
{
  return m_size == 0;
}

//Set whether the list is printable
template <class T>
void LinkedList<T>::setPrintable(bool printable)
{
  PRINTABLE = printable;
}


//Return the front Node
template <class T>
Node<T>* LinkedList<T>::getFront() {
    return m_front;
}
