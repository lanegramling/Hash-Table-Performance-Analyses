
#include <iomanip> //Output formatting convenience
#include "HashDouble.h"

//Constructor - contains initialization of structure.
//Default parameters: m_K = 4, m_P = 5 in this implementation.
template <class T>
HashDouble<T>::HashDouble(int hashSize, int K, int P)
{
  m_tableSize = hashSize;
  m_table = new Bucket<T>[m_tableSize];
  m_K = K;
  m_P = P;
  // PRINTABLE = m_tableSize <= 25;
  PRINTABLE = false; //Suppress unnecessary output for this project
}

//Destructor - proper deletion of the structure implemented here.
template <class T>
HashDouble<T>::~HashDouble()
{
  delete[] m_table;
  if (PRINTABLE) std::cout << "\n\n";
}

//Insert a given value to the Hash table. Hash function implemented here.
//This implementation uses a recursive strategy which takes advantage of double hashing.
//Default Parameter: i = 0
template <class T>
void HashDouble<T>::insert(T value, int i)
{
    //Failed to insert
    if (i > (m_K - 1)) {
      // if (PRINTABLE) std::cout << "\nError: failed to insert " << value << " with double hashing.";
      return;
    }

    //Convenience for accessing current probe point
    Bucket<T>* probePoint = &m_table[(value + (i * (m_P - (value % m_P)))) % m_tableSize];

    //Recursive logic - probing for insertion point
    if (probePoint->getValue()) {
      if (probePoint->getValue() == value) { /* if (PRINTABLE) std::cout << "\nError: duplicate of " << value << " found."; */ }
      else insert(value, i + 1);
    } else {
      probePoint->setValue(value);
      // if (PRINTABLE) std::cout << "\n" << value << " added to table with double hashing.";
      // printLoadFactor();
    }
}

//Erase a given value from the Hash table.
template <class T>
void HashDouble<T>::erase(T value, int i)
{
    //Failed to erase
    if (i > (m_K - 1)) {
        // if (PRINTABLE) std::cout << "\n" << value << " could not be removed with double hashing.";
        return;
    }

    //Convenience for accessing current probe point
    Bucket<T>* probePoint = &m_table[(value + (i * (m_P - (value % m_P)))) % m_tableSize];

    //Recursive logic - probing for removal point
    if (probePoint->checkFlag()) {
        if (probePoint->getValue()) {
          if (probePoint->getValue() == value) { //Removal action
            probePoint->setValue(NULL);
            // if (PRINTABLE) std::cout << "\n" << value << " removed from table with double hashing.";
            // printLoadFactor();
          } else erase(value, i + 1);
        } else erase(value, i + 1);
    } // else  if (PRINTABLE) std::cout << "\n" << value << " was not found.";
}

//Print the Hash table in a readable format.
template <class T>
void HashDouble<T>::print()
{
  std::cout << "\n\n------Hash Table with Double Hashing------";
  for (int i = 0; i < m_tableSize; i++) if (m_table[i].getValue()) std::cout << "\n" << i << ": " << m_table[i].getValue();
  // printLoadFactor();
}

//Find a given value in the Hash table.
template <class T>
bool HashDouble<T>::find(T value, int i)
{
  //Failed to find
  if (i > (m_K - 1)) {
    // if (PRINTABLE) std::cout << "\nFailed to find " << value << " with double hashing.";
    return false;
  }

  //Convenience for accessing current probe point
  Bucket<T>* probePoint = &m_table[(value + (i * (m_P - (value % m_P)))) % m_tableSize];

  //Recursive logic
    if (probePoint->checkFlag()) {
        if (probePoint->getValue()) {
            if (probePoint->getValue() == value) { //Removal action
                // if (PRINTABLE) std::cout << "\n" << value << " found in table with double hashing.";
                return false;
            } else find(value, i + 1);
        } else find(value, i + 1);
    } // else if (PRINTABLE) std::cout << "\n" << value << " was not found.";
    return false;
}

//Print the current load factor of the Hash table.
template <class T>
void HashDouble<T>::printLoadFactor()
{
  float n = 0;
  for (int i = 0; i < m_tableSize; i++) if (m_table[i].getValue() != NULL) n++;
  float loadFactor = n / m_tableSize;
  std::cout << "\nLoad factor with double hashing is " << std::setprecision(2) << std::fixed << loadFactor;
}

template <class T>
void HashDouble<T>::unload()
{
    for (int i = 0; i < m_tableSize; i++) while (m_table[i].getValue()) erase(m_table[i].getValue());
}
