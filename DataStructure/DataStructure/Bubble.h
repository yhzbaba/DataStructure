#pragma once
#include <iostream>
#include "element.h"

using namespace std;

template<class T>
void Bubble(Element<T>* list, int n)
{
	int bound = n;
	Element<T> e;
	while (bound)
	{
		int t = 0;
		for (int i = 1; i < bound; i++)
		{
			if (list[i].GetKey() > list[i + 1].GetKey())
			{
				e = list[i]; list[i] = list[i + 1]; list[i + 1] = e;
				t = i;
			}
		}
		bound = t;
	}
}
