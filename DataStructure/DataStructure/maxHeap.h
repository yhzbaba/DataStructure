#pragma once
#include "maxPriorityQueue.h"
#include "minHeap.h"
#include "myException.h"
#include <sstream>
#include <algorithm>
#include <iterator>
#include <fstream>
#include "arrayStack.h"

using namespace std;

template<class T>
class maxHeap
{
public:
	maxHeap(int initialCapacity = 10);
	~maxHeap() {}
	bool empty() const { return heapSize == 0; }
	int size() const { return heapSize; }
	const T& top()
	{
		if (heapSize == 0)
			throw queueEmpty();
		return heap[1];
	}
	int pop();
	void push(const T&);
	int initialize(T*, int);
	void deactivateArray()
	{
		heap = NULL;
		arrayLength = heapSize = 0;
	}
	void output(ostream& out) const;
private:
	int heapSize;		//个数
	int arrayLength;	//个数+1
	T* heap;
};

template<class T>
maxHeap<T>::maxHeap(int initialCapacity)
{
	if (initialCapacity < 1)
	{
		throw illegalParameterValue();
	}
	arrayLength = initialCapacity + 1;
	heap = new T[arrayLength];
	heapSize = 0;
}

//大根堆插入
template<class T>
void maxHeap<T>::push(const T& theElement)
{
	if (heapSize == arrayLength - 1)
	{
		cout << "Heap is full." << endl;
		return;
	}
	int currentNode = ++heapSize;
	while (currentNode != 1 && heap[currentNode / 2] < theElement)
	{
		heap[currentNode] = heap[currentNode / 2];
		currentNode /= 2;
	}
	heap[currentNode] = theElement;
}

template<class T>
int maxHeap<T>::pop()
{
	int popTime = 0;
	if (heapSize == 0)
		throw queueEmpty();

	heap[1].~T();

	T lastElement = heap[heapSize--];
	int currentNode = 1, child = 2;
	while (child <= heapSize)
	{
		popTime += 2;
		if (child < heapSize && heap[child] < heap[child + 1])
			child++;
		if (lastElement >= heap[child])
			break;
		heap[currentNode] = heap[child];
		currentNode = child;
		child *= 2;
	}
	heap[currentNode] = lastElement;
	return popTime;
}

template<class T>
void maxHeap<T>::output(ostream& out) const
{// Put the list into the stream out.
	copy(heap + 1, heap + heapSize + 1, ostream_iterator<T>(cout, "  "));
}

// overload <<
template <class T>
ostream& operator<<(ostream& out, const maxHeap<T>& x)
{
	x.output(out); return out;
}

template<class T>
int maxHeap<T>::initialize(T* theHeap, int theSize)
{
	int initializeTime = 0;
	delete[] heap;
	heap = theHeap;
	heapSize = theSize;

	//堆化
	for (int root = heapSize / 2; root >= 1; root--)
	{
		T rootElement = heap[root];
		int child = 2 * root;
		
		//为元素rootElement寻找位置
		while (child <= heapSize)
		{
			initializeTime++;
			if (child < heapSize && heap[child] < heap[child + 1])
				child++;
			initializeTime++;
			if (rootElement >= heap[child])
				break;

			heap[child / 2] = heap[child];
			child *= 2;
		}
		heap[child / 2] = rootElement;
	}
	return initializeTime;
}

arrayStack<int> list;

template<class T>
T* heapSort(T* a, int n)
{
	ofstream outFile;
	outFile.open("C:\\Users\\Administrator\\Desktop\\1203Test\\1203.txt", ios::app);
	maxHeap<T> heap(1);
	int result1 = heap.initialize(a, n);
	int result2 = 0;
	for (int i = n - 1; i >= 1; i--)
	{
		T x = heap.top();
		result2 = heap.pop();
		a[i + 1] = x;
	}
	outFile << "比较次数为: " << result1 + result2 << "\n";
	list.push(result1 + result2);
	outFile.close();
	return a;
}

//class jobNode
//{
//private:
//	int id;
//	int time;
//public:
//	friend void makeSchedule(jobNode* a, int n, int m);
//};
//
//class machineNode
//{
//private:
//	int id;
//	int avail;
//public:
//	operator int() const { return avail; }
//	machineNode(int id, int avail)
//	{
//		this->id = id;
//		this->avail = avail;
//	}
//	friend void makeSchedule(jobNode* a, int n, int m);
//};
//
////n  任务数			m  机器数
//void makeSchedule(jobNode* a, int n, int m)
//{
//	if (n < m)
//	{
//		cout << "Schedule each job on a different machine." << endl;
//		return;
//	}
//
//	heapSort(a, n);
//
//	minHeap<machineNode> machineHeap(m);
//	for (int i = 1; i <= m; i++)
//	{
//		machineHeap.push(machineNode(i, 0));
//	}
//
//	//生成调度计划
//	for (int i = n; i >= 1; i--)
//	{
//		machineNode x = machineHeap.top();
//		machineHeap.pop();
//		cout << "Schedule job" << a[i].id << " on machine " << x.id << " from " << x.avail
//			<< " to " << (x.avail + a[i].time) << endl;
//		x.avail += a[i].time;
//		machineHeap.push(x);
//	}
//}