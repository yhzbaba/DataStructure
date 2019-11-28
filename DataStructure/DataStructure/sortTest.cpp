#include <iostream>
#include "shellSort.h"
#include "insertSort.h"
#include "Bubble.h"
#include "quickSort.h"

using namespace std;

int main()
{
	Element<int>* elements = new Element<int>[5];
	for (int i = 0; i < 5; i++)
	{
		elements[i].SetKey(10 - i);
	}
	//Bubble(elements, 4);
	//QSort(elements, 1, 4);
	for (int i = 1; i < 5; i++)
	{
		cout << elements[i].GetKey() << endl;
	}

	return 0;
}
