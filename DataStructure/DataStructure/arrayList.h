#pragma once
#include <iostream>
#include <sstream>
#include <string>
#include <iterator>
#include <algorithm>
#include "linearList.h"
#include "myException.h"


//�ı�һ��һά���鳤��
template<class T>
void changeLength1D(T*& a, int oldLength, int newLength)
{
	if (newLength < 0)
		throw illegalParameterValue("new length must be >= 0");

	T* temp = new T[newLength];
	int number = min(oldLength, newLength);
	copy(a, a + number, temp);
	delete[] a;
	a = temp;
}

template<class T>
class arrayList : public linearList<T>
{
protected:
	void checkIndex(int theIndex)const;
				//������theIndex��Ч�����׳��쳣
	T* element;
	int arrayLength;	//����
	int listSize;		//���Ա�Ԫ�ظ���

public:
	//���졢���ƹ��������
	arrayList(int initialCapacity = 10);
	arrayList(const arrayList<T>&);
	~arrayList() { delete[] element; }

	//ADT����
	bool empty() const { return listSize == 0; }
	int size() const { return listSize; }
	T& get(int theIndex) const;
	int indexOf(const T& theElement) const;
	void erase(int theIndex);
	void insert(int theIndex, const T& theElement);
	void output(ostream& out) const;

	//��������
	int capacity() const { return arrayLength; }
};


//���캯��
template<class T>
arrayList<T>::arrayList(int initialCapacity)
{
	if (initialCapacity < 1)
	{
		ostringstream s;
		s << "Initial capacity = " << initialCapacity << " Must be > 0";
		throw illegalParameterValue(s.str());
	}
	arrayLength = initialCapacity;
	element = new T[arrayLength];
	listSize = 0;
}

//���ƹ��캯��
template<class T>
arrayList<T>::arrayList(const arrayList<T>& theList)
{
	arrayLength = theList.arrayLength;
	listSize = theList.listSize;
	element = new T[arrayLength];
	copy(theList.element, theList.element + listSize, element);
}

//���theIndex���±��Ƿ�Ϸ�
template<class T>
void arrayList<T>::checkIndex(int theIndex) const
{
	if (theIndex < 0 || theIndex >= listSize)
	{
		ostringstream s;
		s << "index = " << theIndex << " size = " << listSize;
		throw illegalIndex(s.str());
	}
}

//get����,����theIndex�±��Ԫ��
template<class T>
T& arrayList<T>::get(int theIndex) const
{
	checkIndex(theIndex);
	return element[theIndex];
}

//����Ԫ��theElement��һ�γ���ʱ������
template<class T>
int arrayList<T>::indexOf(const T& theElement) const
{
	//����Ԫ�ز����ڣ�����-1
	int theIndex = (int)(find(element, element + listSize, theElement) - element);

	if (theIndex == listSize)
		return -1;
	else return theIndex;
}

//ɾ������ΪtheIndex��Ԫ�أ���������ڣ��׳��쳣illegalIndex
template<class T>
void arrayList<T>::erase(int theIndex)
{
	checkIndex(theIndex);

	copy(element + theIndex + 1, element + listSize, element + theIndex);

	element[--listSize].~T();
}

template<class T>
void arrayList<T>::insert(int theIndex, const T& theElement)
{
	if (theIndex <0 || theIndex >listSize)
	{
		ostringstream s;
		s << "index = " << theIndex << " size = " << listSize;
		cout << "Bad init" << endl;
		return;
	}

	if (listSize == arrayLength)
	{
		//����ռ����������鳤�ȱ���
		changeLength1D(element, arrayLength, 2 * arrayLength);
		arrayLength *= 2;
	}

	//��Ԫ������һ��λ��
	for (int i = 0; i < listSize - theIndex + 1; i++)
	{
		element[listSize - i] = element[listSize - i - 1];
	}

	element[theIndex] = theElement;

	listSize++;
}

template<class T>
void arrayList<T>::output(ostream& out) const
{
	copy(element, element + listSize, ostream_iterator<T>(cout, " "));
}

//����<<
template<class T>
ostream& operator<<(ostream& out, const arrayList<T>& x)
{
	x.output(out);
	return out;
}
