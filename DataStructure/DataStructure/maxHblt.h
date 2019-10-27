#pragma once
#include "maxPriorityQueue.h"
#include "binaryTreeNode.h"
#include "myException.h"
#include <sstream>

using namespace std;

template<class T>
class maxHblt : public maxPriorityQueue<T>
{
private:
	binaryTreeNode<T>* root;
	int treeSize;

	void meld(binaryTreeNode<pair<int,T>>*&,
		binaryTreeNode<pair<int,T>>*&);
	/*static void hbltOutput(binaryTreeNode<pair<int,T>>* t)
	{
		cout << t->element.second << " ";
	}*/
public:
	bool empty() const { treeSize == 0; }
	int size() const { return treeSize; }
	const T& top()
	{
		if (treeSize == 0)
			throw queueEmpty();
		return root->element.second;
	}
	void pop();
	void push(const T&);
	void initialize(T*, int);
	void meld(maxHblt<T>& theHblt)
	{
		meld(root, theHblt.root);
		treeSize += theHblt.treeSize;
		theHblt.root = NULL;
		theHblt.treeSize = 0;
	}
};

template<class T>
void maxHblt<T>::meld(binaryTreeNode<pair<int, T>>*& x,
	binaryTreeNode<pair<int, T>>*& y)
{
	if (y == NULL)
	{
		return;
	}
	if (x == NULL)
		return y;
	if (x->element.second < y->element.second)
		swap(x, y);

	meld(x->rightChild, y);

	if (x->leftChild == NULL)
	{
		x->leftChild = x->rightChild;
		x->rightChild = NULL;
		x->element.first = 1;
	}
	else
	{
		if (x->leftChild->element.first < x->rightChild->element.first)
			swap(x->leftChild, x->rightChild);
		x->element.first = x->rightChild->element.first + 1;
	}
}

template<class T>
void maxHblt<T>::push(const T& theElement)
{
	binaryTreeNode<pair<int, T>>* q = new binaryTreeNode<pair<int, T>>(pair<int, T>(1, theElement));
	meld(root, q);
	treeSize++;
}

template<class T>
void maxHblt<T>::pop()
{
	if (root == NULL)
		throw queueEmpty();
	binaryTreeNode<pair<int, T>>* left = root->leftChild,
		* right = root->rightChild;
	delete root;
	root = left;
	meld(root, right);
	treeSize--;
}

template<class T>
void maxHblt<T>::initialize(T* theElements, int theSize)
{
	arrayQueue<binaryTreeNode<pair<int, T>>*> q(theSize);
	treeSize = theSize;
	root = NULL;

	for (int i = 1; i <= theSize; i++)
	{
		q.push(new binaryTreeNode<pair<int, T>>(pair<int, T>(1, theElements[i])));
	}

	for (i = 1; i <= theSize - 1; i++)
	{
		binaryTreeNode<pair<int, T>>* b = q.front();
		q.pop();
		binaryTreeNode<pair<int, T>>* c = q.front();
		q.pop();
		meld(b, c);
		q.push(b);
	}
	if (theSize > 0)
		root = q.front();
}
