#include <iostream>
using namespace std;

template <typename T>

class IGenLinkedList{
public:
		virtual void insertBack(T* data);
		virtual void insertBack(T* data) = 0;
		virtual T* removeFront() = 0;
		virtual T* getElement(int idx) = 0;
		virtual T* remove(T* val) = 0;
		virtual unsigned int getSize() = 0;
		virtual bool isEmpty() = 0;
		virtual void printList();
};
