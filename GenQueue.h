#include <iostream>
using namespace std;
#include "GenLinkedList.h"

template <typename T>
class GenQueue
{
  public:
  GenQueue(); //Constructor
  ~GenQueue(); //Destructor

  void insert(T* d); //Enqueue
  T* remove(); //Dequeue

  //aux functions
  T* peek(); //Returns first element of queue
  bool isFull(); //Returns whether queue is full
  bool isEmpty(); //Returns whether queue is empty
  int getSize(); //Returns queue size

  GenLinkedList<T> *list; //Linked list
};

template <typename T>
GenQueue<T>::GenQueue(){
  //default constructor
  list = new GenLinkedList<T>();
}
template <typename T>
GenQueue<T>::~GenQueue(){
  delete list;
}
template <typename T>
void GenQueue<T>::insert(T* d){
  list->insertBack(d);
}
template <typename T>
T* GenQueue<T>::remove(){
  return list->removeFront();
}
template <typename T>
T* GenQueue<T>::peek(){
  return list->front->data;
}
template <typename T>
bool GenQueue<T>::isFull(){
  return false;
}
template <typename T>
bool GenQueue<T>::isEmpty(){
  return (list->size == 0);
}
template <typename T>
int GenQueue<T>::getSize(){
  return list->size;
}
