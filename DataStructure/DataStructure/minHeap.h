#pragma once
#include "minPriorityQueue.h"
#include "myException.h"
#include <sstream>
#include <algorithm>
#include <iterator>

using namespace std;

template<class T>
class minHeap : public minPriorityQueue<T>
{
public:
	minHeap(int initialCapacity = 10);
	~minHeap() { cout << "Îö¹¹" << endl; }
	bool empty() const { return heapSize == 0; }
	int size() const { return heapSize; }
	const T& top()
	{
		if (heapSize == 0)
			throw queueEmpty();
		return heap[1];
	}
	void pop();
	void push(const T& theElement);
	void initialize(T*, int);
	void deactivateArray()
	{
		heap = NULL;
		arrayLength = heapSize = 0;
	}
	void output(ostream& out) const;
private:
	int heapSize;
	int arrayLength;
	T* heap;
};

template<typename T>
minHeap<T>::minHeap(int initialCapacity)
{
	if (initialCapacity < 1)
	{
		throw illegalParameterValue();
	}
	arrayLength = initialCapacity + 1;
	heap = new T[arrayLength];
	heapSize = 0;
}

template<typename T>
void minHeap<T>::push(const T& theElement)
{
	if (heapSize == arrayLength - 1)
	{
		cout << "Heap is full." << endl;
		return;
	}
	int currentNode = ++heapSize;
	while (currentNode != 1 && heap[currentNode / 2] > theElement)
	{
		heap[currentNode] = heap[currentNode / 2];
		currentNode /= 2;
	}
	heap[currentNode] = theElement;
}

template<class T>
void minHeap<T>::pop()
{
	if (heapSize == 0)
		throw queueEmpty();
	heap[1].~T();

	T lastElement = heap[heapSize--];
	int currentNode = 1, child = 2;
	while (currentNode < heapSize)
	{
		if (child<heapSize && heap[child] > heap[child + 1])
			child++;
		if (lastElement <= heap[child])
			break;
		heap[currentNode] = heap[child];
		currentNode = child;
		child *= 2;
	}
	heap[currentNode] = lastElement;
}

template<class T>
void minHeap<T>::output(ostream& out) const
{
	copy(heap + 1, heap + 1 + heapSize, ostream_iterator<T>(cout, " "));
}

template<class T>
ostream& operator<<(ostream& out, const minHeap<T>& x)
{
	x.output(out); return out;
}

template<class T>
void minHeap<T>::initialize(T* theHeap, int theSize)
{
	delete[] heap;
	heap = theHeap;
	heapSize = theSize;

	for (int root = heapSize / 2; root >= 1; root--)
	{
		T rootElement = heap[root];
		int child = 2 * root;

		while (child <= heapSize)
		{
			if (child<heapSize && heap[child]>heap[child + 1])
				child++;
			if (rootElement <= heap[child])
				break;
			heap[child / 2] = heap[child];
			child *= 2;
		}
		heap[child / 2] = rootElement;
	}
}


