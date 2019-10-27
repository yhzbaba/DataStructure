#pragma once
#include "myException.h"
#include "stack.h"
#include "chainNode.h"
#include <iostream>

using namespace std;

template<class T>
class linkedStack : public stack<T>
{
public:
	linkedStack()
	{
		stackTop = NULL;
		stackSize = 0;
	}
	~linkedStack();
	bool empty() const { return stackSize == 0; }
	int size() const { return stackSize; }
	T& top()
	{
		if (stackSize == 0)
			throw stackEmpty();
		return stackTop->element;
	}
	void pop();
	void push(const T& theElement)
	{
		stackTop = new chainNode<T>(theElement, stackTop);
		stackSize++;
	}
private:
	chainNode<T>* stackTop;	//Õ»¶¥Ö¸Õë
	int stackSize;
};

//Îö¹¹º¯Êý
template<class T>
linkedStack<T>::~linkedStack()
{
	while (stackTop != NULL)
	{
		chainNode<T>* nextNode = stackTop->next;
		delete stackTop;
		stackTop = nextNode;
	}
}

//É¾³ýÕ»¶¥½áµã
template<class T>
void linkedStack<T>::pop()
{
	if (stackSize == 0)
		throw stackEmpty();

	chainNode<T>* nextNode = stackTop->next;
	delete stackTop;
	stackTop = nextNode;
	stackSize--;
}