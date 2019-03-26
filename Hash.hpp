
#include "Hash.h"

//Constructor - contains initialization of structure.
template <class T>
Hash<T>::Hash(int hashSize)
{
  m_hashSize = hashSize;
  m_table = new LinkedList<T>[m_hashSize];
  for(int i = 0; i < m_hashSize; i++) m_table[i].setPrintable(m_hashSize <= 25); //Set printability of table
}

//Destructor - proper deletion of the structure implemented here.
template <class T>
Hash<T>::~Hash()
{
  delete[] m_table;
  // std::cout << "\n\n";
}

//Insert a given value to the Hash table. Hash function implemented here.
template <class T>
void Hash<T>::insert(T value)
{
  m_table[value % m_hashSize].insert(value);
}

//Erase a given value from the Hash table.
template <class T>
void Hash<T>::erase(T value)
{
  m_table[value % m_hashSize].erase(value);
}

//Print the Hash table in a readable format.
template <class T>
void Hash<T>::print()
{
    std::cout << "\n\n-----Hash Table with Chaining------";
    for (int i = 0; i < m_hashSize; i++) {
        if (!m_table[i].isEmpty()) { std::cout << "\n" << i << ": "; m_table[i].print(); }
    }
}

//Find a given value in the Hash table.
template <class T>
bool Hash<T>::find(T value)
{
  return m_table[value % m_hashSize].find(value);
}


//Dump the data from the hash table
template <class T>
void Hash<T>::unload() {
    for (int i = 0; i < m_hashSize; i++) while (m_table[i].getFront()) m_table[i].erase(m_table[i].getFront()->getValue());
}
