#pragma once
#include "element.h"

using namespace std;

/*Shell≈≈–Ú*/
template<class T>
void ShellSort(Element<T>* list, int n)
{
	int gap = n;
	while (gap >= 1)
	{
		gap = gap / 2;
		for (int i = 1; i <= gap; i++)
		{
			for (int j = i + gap; j <= n; j++)
			{
				Element<T> e = list[j];
				int t = j - gap;
				while (e.GetKey() < list[t].GetKey())
				{
					list[t + gap] = list[t];
					t = t - gap;
					if (t < i)
						break;
				}
				list[t + gap] = e;
			}
		}
	}
}
