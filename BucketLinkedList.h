#ifndef BUCKET_LINKED_LIST_H
#define BUCKET_LINKED_LIST_H

#include "Bucket.h"

template <typename T>
class BucketLinkedList
{
public:
  //Constructor.
  BucketLinkedList();

  //Destructor.
  ~BucketLinkedList();

  //Removes the node containing the given value from the list.
  bool erase(T value, Bucket<T>* current=nullptr, Bucket<T>* prev=nullptr);

  //Adds to the end of the list.
  void insert(T value, Bucket<T>* current=nullptr);

  //Prints the full contents of this BucketLinkedList in a readable format.
  void print();

  //Search for a given value in this BucketLinkedList. If not found, returns null.
  Bucket<T>* find(T value);

  //Returns whether this BucketLinkedList is empty.
  bool isEmpty();

private:
  Bucket<T>* m_front; //Pointer to the front of this BucketLinkedList.
  int m_size;       //Size tracking integer, for convenience.


};

#include "BucketLinkedList.hpp"

#endif
