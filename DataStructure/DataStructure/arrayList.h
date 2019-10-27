#pragma once
#include <iostream>
#include <sstream>
#include <string>
#include <iterator>
#include <algorithm>
#include "linearList.h"
#include "myException.h"


//改变一个一维数组长度
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
				//若索引theIndex无效，则抛出异常
	T* element;
	int arrayLength;	//容量
	int listSize;		//线性表元素个数

public:
	//构造、复制构造和析构
	arrayList(int initialCapacity = 10);
	arrayList(const arrayList<T>&);
	~arrayList() { delete[] element; }

	//ADT方法
	bool empty() const { return listSize == 0; }
	int size() const { return listSize; }
	T& get(int theIndex) const;
	int indexOf(const T& theElement) const;
	void erase(int theIndex);
	void insert(int theIndex, const T& theElement);
	void output(ostream& out) const;

	//其他方法
	int capacity() const { return arrayLength; }
};


//构造函数
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

//复制构造函数
template<class T>
arrayList<T>::arrayList(const arrayList<T>& theList)
{
	arrayLength = theList.arrayLength;
	listSize = theList.listSize;
	element = new T[arrayLength];
	copy(theList.element, theList.element + listSize, element);
}

//检查theIndex此下标是否合法
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

//get函数,返回theIndex下标的元素
template<class T>
T& arrayList<T>::get(int theIndex) const
{
	checkIndex(theIndex);
	return element[theIndex];
}

//返回元素theElement第一次出现时的索引
template<class T>
int arrayList<T>::indexOf(const T& theElement) const
{
	//若该元素不存在，返回-1
	int theIndex = (int)(find(element, element + listSize, theElement) - element);

	if (theIndex == listSize)
		return -1;
	else return theIndex;
}

//删除索引为theIndex的元素，如果不存在，抛出异常illegalIndex
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
		//数组空间已满，数组长度倍增
		changeLength1D(element, arrayLength, 2 * arrayLength);
		arrayLength *= 2;
	}

	//把元素右移一个位置
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

//重载<<
template<class T>
ostream& operator<<(ostream& out, const arrayList<T>& x)
{
	x.output(out);
	return out;
}
