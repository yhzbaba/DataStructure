#pragma once
#include <iostream>
#include "linearList.h"
#include <vector>

using namespace std;

template<class T>
class vectorList : public linearList<T>
{
protected:
	void checkIndex(int theIndex) const;
	vector<T>* element;	//�洢���Ա�Ԫ�ص�����
public:
	vectorList(int initialCapacity = 10);
	vectorList(const vectorList<T>&);
	~vectorList() { delete[] element; }

	//ADT����
	bool empty() const { return element->empty(); }
	int size() const { return (int)element->size(); }
	T& get(int theIndex) const;
	int indexOf(const T& theElement) const;
	void erase(int theIndex);
	void insert(int theIndex, const T& theElement);
	void output(ostream& out)const;

	//���ӵķ���
	int capacity() const { return (int)element->capacity(); }

	//���Ա����ʼ�ͽ���λ�õĵ�����
	typedef typename vector<T>::iterator iterator;
	iterator begin() { return element->begin(); }
	iterator end() { return element->end(); }
};

//���캯��
template<class T>
vectorList<T>::vectorList(int initialCapacity)
{
	if (initialCapacity < 1)
	{
		cout << "Bad init" << endl;
		return;
	}

	element = new vector<T>;
	element->reserve(initialCapacity);
}

//���ƹ��캯��
template<class T>
vectorList<T>::vectorList(const vectorList<T>& theList)
{
	element = new vector<T>(*theList.element);
}

//ɾ������ΪtheIndex��Ԫ��
template<class T>
void vectorList<T>::erase(int theIndex)
{
	checkIndex(theIndex);
	element->erase(begin() + theIndex);
}

//������ΪtheIndex������theElement
template<class T>
void vectorList<T>::insert(int theIndex, const T& theElement)
{
	if (theIndex<0 || theIndex>size())
	{
		cout << "Bad index" << endl;
		return;
	}

	element->insert(element->begin() + theIndex, theElement);
}