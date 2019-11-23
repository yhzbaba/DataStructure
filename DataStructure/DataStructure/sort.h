#pragma once
#include <iostream>
using namespace std;

class Element
{
public:
	int GetKey()const { return key; }
	void SetKey(int k) { key = k; }
private:
	int key;
};

//²åÈëÅÅĞò
//½«ĞòÁĞlist[1],list[2],...,list[n]ÅÅĞò
void InsertionSort(Element* list, int n)
{
	Element e;
	list[0].SetKey(-100);
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


//ShellÅÅĞò
void ShellSort(Element* list, int n)
{
	int gap = n;
	int i;
	while (gap >= 1)
	{
		gap = gap / 2;
		for (i = 0; i < gap; i++)
		{
			Element e;
			for (int j = i + gap; j <= n; j = j + gap)
			{
				e = list[j];
				int t = j - gap;
				while (e.GetKey() < list[t].GetKey())
				{
					list[t + gap] = list[t];
					t = t - gap;
					if (t <= i)
						break;
				}
				list[t + gap] = e;
			}
		}
	}
}

//Ã°ÅİÅÅĞòËã·¨
void Bubble(Element* R, int n)
{
	int bound = n;
	Element e;
	int t;
	while (bound)
	{
		t = 0;
		for (int j = 1; j < bound; j++)
		{
			if (R[j].GetKey() > R[j + 1].GetKey())
			{
				e = R[j]; R[j] = R[j + 1]; R[j + 1] = e;
				t = j;
			}
		}
		bound = t;
	}
}
