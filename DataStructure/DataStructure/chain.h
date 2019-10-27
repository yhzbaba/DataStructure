#pragma once
#include "myException.h"
#include "linearList.h"
#include "chainNode.h"
#include <iostream>
#include <sstream>

using namespace std;



template<class T>
class chain : public linearList<T>
{
protected:
	void checkIndex(int theIndex) const;
	chainNode<T>* firstNode;
	int listSize;
public:
	chain(int initialCapacity = 10);
	chain(const chain<T>&);
	~chain();

	bool empty() const { return listSize == 0; }
	int size() const { return listSize; }
	T& get(int theIndex) const;
	int indexOf(const T& theElement) const;
	void erase(int theIndex);
	void insert(int theIndex, const T& theElement);
	void output(ostream& out) const;

	void clear();
	void push_back(const T& theElement);
	void binSort(int range);
};

template<class T>
void chain<T>::checkIndex(int theIndex) const
{
	if (theIndex < 0 || theIndex >= listSize)
	{
		throw illegalIndex("invalid index.");
		return;
	}
}

template<class T>
chain<T>::chain(int initialCapacity)
{
	if (initialCapacity < 1)
	{
		cout << "Bad init" << endl;
		return;
	}
	firstNode = NULL;
	listSize = 0;
}

//���ƹ��캯��
template<class T>
chain<T>::chain(const chain<T>& theList)
{
	listSize = theList.listSize;
	if (listSize == 0)
	{
		firstNode = NULL;
		return;
	}

	chainNode<T>* sourceNode = theList.firstNode;
					//Ҫ��������theList�Ľڵ�
	firstNode = new chainNode<T>(sourceNode->element);
					//��������theList����Ԫ��
	sourceNode = sourceNode->next;
	chainNode<T>* targetNode = firstNode;
					//��ǰ����*this�����һ���ڵ�
	while (sourceNode != NULL)
	{
		//����ʣ��Ԫ��
		targetNode->next = new chainNode<T>(sourceNode->element);
		sourceNode = sourceNode->next;
		targetNode = targetNode->next;
	}
	targetNode->next = NULL;
}

//��������
template<class T>
chain<T>::~chain()
{
	while (firstNode != NULL)
	{
		chainNode<T>* nextNode = firstNode->next;
		delete firstNode;
		firstNode = nextNode;
	}
}

//����get
template<class T>
T& chain<T>::get(int theIndex) const
{
	checkIndex(theIndex);

	chainNode<T>* currentNode = firstNode;
	for (int i = 0; i < theIndex; i++)
	{
		currentNode = currentNode->next;
	}

	return currentNode->element;
}

//����Ԫ��theElement�״γ���ʱ������
template<class T>
int chain<T>::indexOf(const T& theElement) const
{
	//��Ԫ�ز����ڷ���-1
	chainNode<T>* currentNode = firstNode;
	int index = 0;
	while (currentNode != NULL && currentNode->element != theElement)
	{
		currentNode = currentNode->next;
		index++;
	}

	if (currentNode == NULL)
		return -1;
	else
		return index;
}

//ɾ������ΪtheIndex��Ԫ��
template<class T>
void chain<T>::erase(int theIndex)
{
	checkIndex(theIndex);

	chainNode<T>* deleteNode;
	if (theIndex == 0)
	{
		deleteNode = firstNode;
		firstNode = firstNode->next;
	}
	else
	{
		chainNode<T>* p = firstNode;
		for (int i = 0; i < theIndex - 1; i++)
		{
			p = p->next;
		}
		deleteNode = p->next;
		p->next = p->next->next;
	}
	listSize--;
	delete deleteNode;
}

//����Ԫ��theELement��ʹ������ΪtheIndex
template<class T>
void chain<T>::insert(int theIndex, const T& theElement)
{
	if (theIndex < 0 || theIndex > listSize)
	{
		cout << "Invalid insert index." << endl;
		return;
	}

	if (theIndex == 0)
	{
		firstNode = new chainNode<T>(theElement, firstNode);
	}
	else
	{
		chainNode<T>* p = firstNode;
		for (int i = 0; i < theIndex - 1; i++)
		{
			p = p->next;
		}
		p->next = new chainNode<T>(theElement, p->next);
	}
	listSize++;
}

//�������
template<class T>
void chain<T>::output(ostream& out) const
{
	for (chainNode<T>* currentNode = firstNode;
		currentNode != NULL;
		currentNode = currentNode->next)
	{
		out << currentNode->element << " ";
	}
}

//����<<
template<class T>
ostream& operator<<(ostream& out, const chain<T>& x)
{
	x.output(out);
	return out;
}

//ɾ���������нڵ�
template<class T>
void chain<T>::clear()
{
	while (firstNode != NULL)
	{
		chainNode<T>* nextNode = firstNode->next;
		delete firstNode;
		firstNode = nextNode;
	}
	listSize = 0;
}

//����β�˲���
template<class T>
void chain<T>::push_back(const T& theElement)
{
	chainNode<T>* newNode = new chainNode<T>(theElement, NULL);
	if (firstNode == NULL)
	{
		firstNode = newNode;
	}
	else
	{
		chainNode<T>* currentNode = firstNode;
		for (int i = 0; i < listSize; i++)
		{
			currentNode = currentNode->next;
		}
		currentNode->next = newNode;
	}
	listSize++;
}

//binSort		2
template<class T>
void chain<T>::binSort(int range)
{
	//��������ʼ������
	chainNode<T>** bottom, ** top;
	bottom = new chainNode<T>[range + 1];
	top = new chainNode<T>[range + 1];
	for (int b = 0; b <= range; b++)
		bottom[b] = NULL;

	//������Ľڵ���䵽����
	for (; firstNode != NULL; firstNode = firstNode->next)
	{
		int theBin = firstNode->element;
		if (bottom[theBin] == NULL)
			bottom[theBin] = top[theBin] = firstNode;
		else//���Ӳ���
		{
			top[theBin]->next = firstNode;
			top[theBin] = firstNode;
		}
	}

	//�������еĽڵ��ռ�����������
	chainNode<T>* y = NULL;
	for (int theBin = 0; theBin <= range; theBin++)
	{
		if (bottom[theBin] != NULL)
		{
			//˵�����Ӳ���
			if (y == NULL)
			{
				//��һ���ǿ�����
				firstNode = bottom[theBin];
			}
			else
			{
				y->next = bottom[theBin];
			}
			y = top[theBin];
		}
	}
	if (y != NULL)
		y->next = NULL;

	delete[] bottom;
	delete[] top;
}

