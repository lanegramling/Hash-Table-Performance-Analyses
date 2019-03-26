#include <iostream>

#include "Bucket.h"
#include "BucketLinkedList.h"

/* NOTE This BucketLinkedList implementation has been slightly modified for use with
        Hash.h. Modifications:
         - insert() method inserts to the front of the list instead of end.
         - All occurances of 'list' in I/O have been replaced with table.

        A BucketLinkedList is simply a LinkedList whose Bucket container has been swapped
        with a slightly modified version - the Bucket.
*/



//Constructor
template <class T>
BucketLinkedList<T>::BucketLinkedList()
{
  m_size = 0;
  m_front = nullptr;
}

//Destructor
template <class T>
BucketLinkedList<T>::~BucketLinkedList()
{
  while (!isEmpty()) erase(m_front->getValue());
}

//Erases the Bucket containing the given value from this BucketLinkedList.
template <class T>
bool BucketLinkedList<T>::erase(T value, Bucket<T>* current, Bucket<T>* prev)
{
  //Validation Logic
  if (isEmpty()) {std::cout << "\nError: " << value << " not in table."; return false; }
  if (current == nullptr) {
    if (prev == nullptr) current = m_front; //Designed such that when both are nullptr, we're at the beginning, and...
    else { std::cout << "\nError: " << value << " not in table."; return false; }                   //when current is nullptr but prev is not, we're at the end AND the Value was never found
  }

  //Evaluate the Bucket
  if (current->getValue() == value) { //Found the value, now remove it.
    if (current == m_front) m_front = m_front->getNext();  //Edge case: Adjust front pointer if removing first value.
    if (prev != nullptr) prev->setNext(current->getNext()); //Re-link if needed
    m_size--;
    delete current;
    // std::cout << "\n" << value << " removed from table.";
    return true;
  } else { //Keep searching
    return erase(value, current->getNext(), current);
  }
}

//Adds a Bucket to the FRONT of this BucketLinkedList. Abort upon detection of a duplicate value.
template <class T>
void BucketLinkedList<T>::insert(T value, Bucket<T>* current)
{
  if (isEmpty()) {   //Validate existence of front Bucket.
    Bucket<T>* newBucket = new Bucket<T>(value);
    m_front = newBucket;
    m_size++;
    return;
  }
  if (current == nullptr) current = m_front; //Designed so this only occurs at entry of recursion. Allows usage of default parameter.
  if (current->getValue() == value) { //Disallow duplicates
    std::cout << "\nError: " << value << " already exists in table.";
    return;
  }
  if (current->getNext() != nullptr) insert(value, current->getNext()); //Recurse to end
  else {  //Time to insert - Create a new Bucket and pin it to the FRONT.
    Bucket<T>* newBucket = new Bucket<T>(value);
    newBucket->setNext(m_front); //Pin to front
    m_front = newBucket; //Update pointer to front
    m_size++;
    // std::cout << "\n" << value << " added to table.";
  }
}

template <class T>
void BucketLinkedList<T>::print()
{
  // if (isEmpty()) std::cout << "(Empty)";
  Bucket<T>* current = m_front;
  while (current != nullptr) {
    std::cout << current->getValue() << " ";
    current = current->getNext();
  }
}

template <class T>
Bucket<T>* BucketLinkedList<T>::find(T value)
{
    Bucket<T>* current = m_front;

    while (current != nullptr)
      if (current->getValue() == value) return current;
      else current = current->getNext();

    return nullptr;
}

//Returns whether this BucketLinkedList is empty.
template <class T>
bool BucketLinkedList<T>::isEmpty()
{
  return m_size == 0;
}
