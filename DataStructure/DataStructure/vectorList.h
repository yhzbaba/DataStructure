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
	vector<T>* element;	//存储线性表元素的向量
public:
	vectorList(int initialCapacity = 10);
	vectorList(const vectorList<T>&);
	~vectorList() { delete[] element; }

	//ADT方法
	bool empty() const { return element->empty(); }
	int size() const { return (int)element->size(); }
	T& get(int theIndex) const;
	int indexOf(const T& theElement) const;
	void erase(int theIndex);
	void insert(int theIndex, const T& theElement);
	void output(ostream& out)const;

	//增加的方法
	int capacity() const { return (int)element->capacity(); }

	//线性表的起始和结束位置的迭代器
	typedef typename vector<T>::iterator iterator;
	iterator begin() { return element->begin(); }
	iterator end() { return element->end(); }
};

//构造函数
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

//复制构造函数
template<class T>
vectorList<T>::vectorList(const vectorList<T>& theList)
{
	element = new vector<T>(*theList.element);
}

//删除索引为theIndex的元素
template<class T>
void vectorList<T>::erase(int theIndex)
{
	checkIndex(theIndex);
	element->erase(begin() + theIndex);
}

//在索引为theIndex处插入theElement
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