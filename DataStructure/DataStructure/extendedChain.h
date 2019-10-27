#pragma once
/*
	声明一个数据成员lastNode
	提供改进的erase和insert代码
	定义在linearList中剩余的纯虚函数
	实现clear和push_back*/

#include <iostream>
#include <sstream>
#include <string>
#include "extendedLinearList.h"
#include "chain.h"
#include "chainNode.h"
#include "myException.h"

using namespace std;

template<class T>
class extendedChain :public extendedLinearList<T>, public chain<T>
{
public:
	//constructor and copy constructor
	extendedChain(int initialCapacity = 10) :chain<T>(initialCapacity) {}
	extendedChain(const extendedChain<T>& c) :chain<T>(c) {}

	//ADT
	bool empty() const { return listSize == 0; }
	int size() const { return listSize; }
	T& get(int theIndex)const
	{
		return chain<T>::get(theIndex);
	}
	int indexOf(const T& theElement) const
	{
		return chain<T>::indexOf(theElement);
	}
	void erase(int theIndex);
	void insert(int theIndex, const T& theElement);
	void clear()
	{
		while (firstNode != NULL)
		{
			chainNode<T>* nextNode = firstNode->next;
			delete firstNode;
			firstNode = nextNode;
		}
		listSize == 0;
	}
	void push_back(const T& theElement);
	void output(ostream& out) const
	{
		chain<T>::output(out);
	}
	void zero()
	{
		firstNode = NULL;
		listSize = 0;
	}
protected:
	chainNode<T>* lastNode;
};

//erase
template<class T>
void extendedChain<T>::erase(int theIndex)
{
	if (theIndex >= listSize)
	{
		cout << "theIndex must be < listSize" << endl;
		return;
	}

	chainNode<T>* deleteNode;
	if (theIndex == 0)
	{
		deleteNode = firstNode;
		firstNode = firstNode->next;
		delete deleteNode;
	}
	else
	{
		chainNode<T>* p = firstNode;
		for (int i = 0; i < theIndex - 1; i++)
			p = p->next;
		deleteNode = p->next;
		p->next = deleteNode->next;
		//注意这里是多出来的步骤
		if (deleteNode == lastNode)
			lastNode = p;
		delete deleteNode;
	}
	listSize--;
}

//insert
template<class T>
void extendedChain<T>::insert(int theIndex, const T& theElement)
{
	if (theIndex <= 0 || theIndex > listSize)
	{
		cout << "Invalid insert index." << endl;
		return;
	}

	if (theIndex == 0)
	{
		firstNode = new chainNode<T>(theElement, firstNode);
		if (listSize == 0)
			lastNode = firstNode;
	}
	else
	{
		chainNode<T>* p = firstNode;
		for (int i = 0; i < theIndex - 1; i++)
		{
			p = p->next;
		}

		p->next = new chainNode<T>(theElement, p->next);
		if (listSize == theIndex)
			lastNode = p->next;
	}
	listSize++;
}

//push_back
template<class T>
void extendedChain<T>::push_back(const T& theElement)
{
	chainNode<T>* newNode = new chainNode<T>(theElement, NULL);
	if (firstNode == NULL)
		firstNode = lastNode = newNode;
	else
	{
		lastNode->next = newNode;
		lastNode = newNode;
	}
	listSize++;
}
