#pragma once
#include "element.h"

using namespace std;

//直接插入排序，将序列list[1],list[2]...list[n]排序
template<class T>
void InsertSortA(Element<T>* list, int n)
{
	Element<T> e;
	list[0].SetKey(-1000);
	for (int j = 2; j <= n; j++)
	{
		e = list[j];
		int i = j - 1;
		while (e.GetKey() < list[i].GetKey())
		{
			list[i + 1] = list[i];
			i--;
		}
		list[i + 1] = e;
	}
}
