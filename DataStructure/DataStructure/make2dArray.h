#pragma once

using namespace std;

template<class T>
void make2dArray(T**& x, int numberOfRows, int numberOfColumns)
{
	//create pointersfor the rows
	x = new T * [numberOfRows];

	// get memory for each row
	for (int i = 0; i < numberOfRows; i++)
	{
		x[i] = new T[numberOfColumns];
	}
}
