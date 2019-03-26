
#include "Node.h"

template <class T>
Node<T>::Node(T value, Node<T>* next)
{
 m_value = value;
 m_next = next;
}

template <class T>
void Node<T>::setValue(T value) { m_value = value; }

template <class T>
T Node<T>::getValue() { return m_value; }

template <class T>
void Node<T>::setNext(Node<T>* next) { m_next = next; }

template <class T>
Node<T>* Node<T>::getNext() { return m_next; }
