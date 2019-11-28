#pragma once
#include "element.h"
#include "arrayStack.h"
#include <iostream>

using namespace std;

template<class T>
void Interchange(Element<T>* list, int m, int n)
{
	Element<T> e = list[m];
	list[m] = list[n];
	list[n] = e;
}

template<class T>
int Partition(Element<T>* list, int m, int n)
{
	Interchange(list, (int)(m + n) / 2, m + 1);
	if (list[m + 1].GetKey() > list[n].GetKey())
		Interchange(list, m + 1, n);
	if (list[m].GetKey() > list[n].GetKey())
		Interchange(list, m, n);
	if (list[m + 1].GetKey() > list[m].GetKey())
		Interchange(list, m + 1, m);
	int i = m;
	int j = n + 1;
	int k = list[m].GetKey();
	while (i < j)
	{
		i++;
		while (list[i].GetKey() < k)
			i++;

		j--;
		while (list[j].GetKey() > k)
			j--;
		if (i < j)
			Interchange(list, i, j);
	}
	Interchange(list, m, j);
	return j;
}

template<class T>
void QSort(Element<T>* R, int m, int n)
{
	if (m < n)
	{
		int j = Partition(R, m, n);
		QSort(R, m, j - 1);
		QSort(R, j + 1, n);
	}
}

/*快速排序的非递归算法*/
//不明白
