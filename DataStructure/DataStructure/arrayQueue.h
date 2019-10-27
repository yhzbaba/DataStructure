#pragma once

#include "queue.h"
#include "myException.h"
#include <sstream>

using namespace std;

template<class T>
class arrayQueue : public queue<T>
{
public:
	arrayQueue(int initialCapacity = 10);
	~arrayQueue() { delete[] queue; }
	bool empty() const { return theFront == theBack; }
	int size() const
	{
		return (theBack - theFront + arrayLength) % arrayLength;
	}
	T& front()
	{
		if (theFront == theBack)
			throw queueEmpty();
		return queue[(theFront + 1) % arrayLength];
	}
	T& back()
	{
		if (theFront == theBack)
			throw queueEmpty();
		return queue[theBack];
	}
	void pop()
	{
		if (theFront == theBack)
			throw queueEmpty();
		theFront = (theFront + 1) % arrayLength;
		queue[theFront].~T();
	}
	void push(const T& theElement);
private:
	int theFront;
	int theBack;
	int arrayLength;
	T* queue;
};

template<class T>
arrayQueue<T>::arrayQueue(int initialCapacity)
{
	if (initialCapacity < 1)
	{
		cout << "Bad initialCapacity." << endl;
		return;
	}
	arrayLength = initialCapacity;
	queue = new T[arrayLength];
	theFront = 0;
	theBack = 0;
}


//Add theElement to queue.
template<class T>
void arrayQueue<T>::push(const T& theElement)
{
	if ((theBack + 1) % arrayLength == theFront)
	{
		cout << "¶ÓÁÐÒÑÂú" << endl;
		return;
	}
	theBack = (theBack + 1) % arrayLength;
	queue[theBack] = theElement;
}

