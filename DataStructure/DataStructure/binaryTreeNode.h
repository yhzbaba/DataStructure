#pragma once
#include <iostream>
#include <vector>
#include "arrayQueue.h"
#include "arrayStack.h"
using namespace std;
/*
	10.26	全部重写了一遍
*/

template<class T>
struct binaryTreeNode
{
	T element;
	binaryTreeNode<T>* leftChild;
	binaryTreeNode<T>* rightChild;

	binaryTreeNode() { leftChild = rightChild = NULL; }
	binaryTreeNode(const T& theElement)
	{
		element(theElement);
		leftChild = rightChild = NULL;
	}
	binaryTreeNode(const T& theElement, binaryTreeNode<T>* theLeftChild, binaryTreeNode<T>* theRightChild)
	{
		element = theElement;
		leftChild = theLeftChild;
		rightChild = theRightChild;
	}
};

//visit函数
template<class T>
void visit(binaryTreeNode<T>* x)
{
	cout << x->element << ' ';
}

//前序遍历
template<class T>
void preOrder(binaryTreeNode<T>* t)
{
	if (t != NULL)
	{
		visit(t);
		preOrder(t->leftChild);
		preOrder(t->rightChild);
	}
}

//中序遍历
template<class T>
void inOrder(binaryTreeNode<T>* t)
{
	if (t != NULL)
	{
		inOrder(t->leftChild);
		visit(t);
		inOrder(t->rightChild);
	}
}

//后序遍历
template<class T>
void postOrder(binaryTreeNode<T>* t)
{
	if (t != NULL)
	{
		postOrder(t->leftChild);
		postOrder(t->rightChild);
		visit(t);
	}
}

//后缀转中缀
template<class T>
void infix(binaryTreeNode<T>* t)
{
	if (t != NULL)
	{
		cout << '(';
		infix(t->leftChild);
		cout << t->element;
		infix(t->rightChild);
		cout << ')';
	}
}

//层次遍历
template<class T>
void levelOrder(binaryTreeNode<T>* t)
{
	arrayQueue<binaryTreeNode<T>*> q;
	while (t != NULL)
	{
		visit(t);

		if (t->leftChild != NULL)
			q.push(t->leftChild);
		if (t->rightChild != NULL)
			q.push(t->rightChild);

		try
		{
			t = q.front();
		}
		catch (queueEmpty)
		{
			return;
		}
		q.pop();
	}
}


//NIO		4
template<class T>
void nio(binaryTreeNode<T>* t)
{
	if (t == NULL)
		return;

	arrayStack<binaryTreeNode<T>*> aStack;
	while (t != NULL || !aStack.empty())
	{
		while (t != NULL)
		{
			aStack.push(t);
			t = t->leftChild;
		}
		if (aStack.empty())
		{
			return;
		}
		t = aStack.top();
		aStack.pop();
		cout << t->element << endl;
		t = t->rightChild;
	}
}



//NPO
template<class T>
class AssBinTreeNode
{
private:
	binaryTreeNode<T>* ptr;
	int flag;
public:
	AssBinTreeNode(binaryTreeNode<T>* p = NULL, int i = 0) :ptr(p), flag(i) {}
	int GetFlag() { return flag; }
	void SetFlag(int i) { flag = i; }
	binaryTreeNode<T>* GetPtr() { return ptr; }
	void SetPtr(binaryTreeNode<T>* p) { ptr = p; }
};

//			4
template<class T>
void npo(binaryTreeNode<T>* t)
{
	if (t == NULL)
		return;

	arrayStack<AssBinTreeNode<T>*> aStack;
	AssBinTreeNode<T>* ass;
	AssBinTreeNode<T>* lass;
	AssBinTreeNode<T>* rass;
	ass = new AssBinTreeNode<T>();
	ass->SetFlag(0);
	ass->SetPtr(t);
	aStack.push(ass);
	int i = 0;
	while (!aStack.empty())
	{
		ass = aStack.top();
		t = ass->GetPtr();
		i = ass->GetFlag();
		if (i == 0)
		{
			ass->SetFlag(1);
			aStack.push(ass);
			if (t->leftChild != NULL)
			{
				lass = new AssBinTreeNode<T>(t->leftChild, 0);
				lass->SetFlag(0);
				aStack.push(lass);
			}
		}
		if (i == 1)
		{
			ass->SetFlag(2);
			aStack.push(ass);
			if (t->rightChild != NULL)
			{
				rass = new AssBinTreeNode<T>(t->rightChild, 0);
				rass->SetFlag(0);
				aStack.push(rass);
			}
		}
		if (i == 2)
			cout << t->element << endl;
	}
}


//CBT			2
template<class T>
binaryTreeNode<T>* CreateBinTree(T tostop)
{
	binaryTreeNode<T>* t, * t1, * t2;
	T item;
	cin >> item;
	if (item == tostop)
	{
		t = NULL;
		return t;
	}
	else
	{
		if (!(t = new binaryTreeNode<T>(item, NULL, NULL)))
			return NULL;
		t1 = CreateBinTree(tostop);
		t->leftChild = t1;
		t2 = CreateBinTree(tostop);
		t->rightChild = t2;
		return t;
	}
}

//CopyTree		2
template<class T>
binaryTreeNode<T>* CopyTree(binaryTreeNode<T>* t)
{
	if (t == NULL)
		return NULL;
	binaryTreeNode<T>* newlptr, * newrptr;
	if (t->leftChild != NULL)
		newlptr = CopyTree(t->leftChild);
	else
		newlptr = NULL;
	if (t->rightChild != NULL)
		newrptr = CopyTree(t->rightChild);
	else
		newrptr = NULL;
	binaryTreeNode<T>* newNode = new binaryTreeNode<T>(t->element, newlptr, newrptr);
	return newNode;
}

//Father	在t中寻找p的父亲		2
template<class T>
binaryTreeNode<T>* Father(binaryTreeNode<T>* t, binaryTreeNode<T>* p)
{
	binaryTreeNode<T>* q;
	if (t == NULL || p == NULL)
		return NULL;
	if (t->leftChild == p || t->rightChild == p)
		return t;
	binaryTreeNode<T>* qL = Father(t->leftChild, p);
	if (qL != NULL)
	{
		q = qL;
		return q;
	}
	else
	{
		return Father(t->rightChild, p);
	}
}

//Find			2
template<class T>
binaryTreeNode<T>* Find(binaryTreeNode<T>* t, const T& item)
{
	binaryTreeNode<T>* p, * q;
	if (t == NULL)
		return NULL;
	if (t->element == item)
		return t;
	p = Find(t->leftChild, item);
	if (p != NULL)
	{
		return p;
	}
	else
	{
		q = Find(t->rightChild, item);
		return q;
	}
}

//Del
template<class T>
void Del(binaryTreeNode<T>* t)
{
	if (t != NULL)
	{
		Del(t->leftChild);
		Del(t->rightChild);
		delete t;
	}
}

//结点t的左侧插入data域为item的结点
template<class T>
void InsertLeft(binaryTreeNode<T>* t, T item)
{
	if (t == NULL)
		return;
	binaryTreeNode<T>* p = new binaryTreeNode<T>(item);
	p->leftChild = t->leftChild;
	t->leftChild = p;
}

//删除结点
template<class T>
void DelSubtree(binaryTreeNode<T>* root,binaryTreeNode<T>* t)
{
	if (t == NULL)
		return;
	if (t == root)
	{
		delete t;
		root = NULL;
		return;
	}
	binaryTreeNode<T>* p, * q;
	p = t;
	q = Father(root, p);
	if (q)
	{
		if (q->leftChild == p)
			q->leftChild = NULL;
		if (q->rightChild == p)
			q->rightChild = NULL;
	}
	delete p;
}

//确认树的高度		2
template<class T>
int getHeight(binaryTreeNode<T>* t)
{
	int h = 0, h1, h2;
	if (t == NULL)
		return 0;

	h1 = getHeight(t->leftChild);
	h2 = getHeight(t->rightChild);
	if (h1 > h2)
		h = h1 + 1;
	else
		h = h2 + 1;
	return h;
}

//统计树的结点数		2
template<class T>
int getNodeCount(binaryTreeNode<T>* t)
{
	if (t == NULL)
		return 0;
	int lCount = getNodeCount(t->leftChild);
	int rCount = getNodeCount(t->rightChild);
	int ret = lCount + rCount + 1;
	return ret;
}

//计算树的宽度		2
template<class T>
int widthOfBinaryTree(binaryTreeNode<T>* pNode)
{
	if (pNode == NULL)
		return 0;
	arrayQueue<T> aQueue;
	int maxWidth = 1;
	aQueue.push(pNode);
	while (true)
	{
		int length = aQueue.size();
		if (length == 0)
			break;
		while (length > 0)
		{
			binaryTreeNode<T>* temp = aQueue.front();
			aQueue.pop();
			length--;
			if (temp->leftChild != NULL)
				aQueue.push(temp->leftChild);
			if (temp->rightChild != NULL)
				aQueue.push(temp->rightChild);
		}
		//更新maxWidth的值
		maxWidth = maxWidth > aQueue.size() ? maxWidth : aQueue.size();
	}
	return maxWidth;
}

template<class T>
vector<int> allWidthOfBinaryTree(binaryTreeNode<T>* pNode)
{
	vector<int> ret;
	arrayQueue<binaryTreeNode<T>*> aQueue;
	aQueue.push(pNode);
	while (true)
	{
		int length = aQueue.size();
		if (length == 0)
			break;
		ret.push_back(length);
		while (length > 0)
		{
			binaryTreeNode<T>* temp = aQueue.front();
			if (temp->leftChild != NULL)
				aQueue.push(temp->leftChild);
			if (temp->rightChild != NULL)
				aQueue.push(temp->rightChild);
			length--;
		}
	}
	return ret;
}