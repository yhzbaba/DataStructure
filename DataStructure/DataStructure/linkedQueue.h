#pragma once
#include "queue.h"
#include "chainNode.h"
#include "myException.h"
#include <sstream>

using namespace std;

template<class T>
class linkedQueue : public queue<T>
{
private:
	chainNode<T>* queueFront;
	chainNode<T>* queueBack;
	int queueSize;
public:
	linkedQueue(int initialCapacity = 10)
	{
		queueFront = NULL;
		queueBack = NULL;
		queueSize = 0;
	}
	~linkedQueue();
	bool empty() const
	{
		return queueSize == 0;
	}
	int size() const
	{
		return queueSize;
	}
	T& front()
	{
		if (queueSize == 0)
		{
			cout << "No front element." << endl;
			return;
		}
		return queueFront->element;
	}
	T& back()
	{
		if (queueSize == 0)
		{
			cout << "No back element." << endl;
			return;
		}
		return queueBack->element;
	}
	void pop();
	void push(const T&);
};

template<class T>
linkedQueue<T>::~linkedQueue()
{
	while (queueFront != NULL)
	{
		chainNode<T>* nextNode = queueFront->next;
		delete queueFront;
		queueFront = nextNode;
	}
}

//出队
template<class T>
void linkedQueue<T>::pop()
{
	if (queueSize == 0)
	{
		cout << "No elements." << endl;
		return;
	}
	chainNode<T> nextNode = queueFront->next;
	delete queueFront;
	queueFront = nextNode;
	queueSize--;
}

//入队
template<class T>
void linkedQueue<T>::push(const T& t)
{
	chainNode<T>* newNode = new chainNode<T>(t, NULL);

	if (queueSize == 0)
		queueFront = newNode;
	else
		queueBack->next = newNode;
	queueBack = newNode;

	queueSize++;
}
