#ifndef HASH_H
#define HASH_H

#include "LinkedList.h"

template <class T>
class Hash
{

public:

  //Constructor.
  Hash(int hashSize);

  //Destructor.
  ~Hash();

  //Insert an entry to the Hash table. Hash function implemented here.
  void insert(T value);

  //Remove an entry from the Hash table.
  void erase(T value);

  //Find a given value in the Hash table.
  bool find(T value);

  //Print out the Hash table in a readable format.
  void print();
  
  //Dump the data from the hash table
  void unload();

private:
    int m_hashSize;
    LinkedList<T>* m_table; //Our table will use % m_hashSize for hash function.

};

#include "Hash.hpp"

#endif
