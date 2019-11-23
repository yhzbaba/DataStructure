#pragma once
#include <iostream>
#include "arrayStack.h"
#include "arrayQueue.h"

using namespace std;

//左儿子右兄弟


/*树节点类TreeNode声明*/
template<class T>
class TreeNode
{
private:
	T data;
	TreeNode<T>* firstChild, * nextBrother;
public:
	TreeNode(T value = 0, TreeNode<T> * L = NULL, TreeNode<T> * R = NULL) :
		data(value), firstChild(L), nextBrother(R) {}
	TreeNode<T>* GetFirstChild() const { return firstChild; }
	void SetFirstChild(TreeNode<T>* t) const { firstChild = t; }
	TreeNode<T>* GetNextBrother() const { return nextBrother; }
	void SetNextBrother(TreeNode<T>* t) { nextBrother = t; }
	T& GetData() { return data; }
	void SetData(const T& item) { data = item; }
};

/*树类Tree的声明*/
template<class T>
class Tree
{
private:
	TreeNode<T>* root;			//根节点
	T stop;
public:
	Tree() { root = NULL; }
	//返回结点p的大儿子结点
	TreeNode<T>* FirstChild(TreeNode<T>* p);

	//返回结点p的下一个兄弟结点
	TreeNode<T>* NextBrother(TreeNode<T>* p);


	//先根遍历以t为根节点的树
	void PreOrder(TreeNode<T>* p);
	
	//非递归先根遍历以t为根节点的树
	void NorecPreOrder(TreeNode<T>* t);

	//层次遍历以t为根节点的树
	void LevelOrder(TreeNode<T>* t);

	//在以t为根节点的树中搜索值为target的结点
	TreeNode<T>* FindTarget(TreeNode<T>* t, T target);

	//在树t中搜索p的父节点
	TreeNode<T>* FindFather(TreeNode<T>* t, TreeNode<T>* p);

	//在以t为根的树中删除以p为根的子树
	void DelSubtree(TreeNode<T>* t, TreeNode<T>* p);
	void Del(TreeNode<T>* p);


	//其他操作
	T GetStop() { return stop; }
	void SetStop(T tostop) { stop = tostop; }
	TreeNode<T>* GetRoot() { return root; }
	void SetRoot(TreeNode<T>* t) { root = t; }
	TreeNode<T>* Create();
	void CreateTree(T tostop);
	void PostOrder(TreeNode<T>* t);
};

template<class T>
TreeNode<T>* Tree<T>::FirstChild(TreeNode<T>* p)
{
	if (p != NULL && (p->GetFirstChild()) != NULL)
		return p->GetFirstChild();
	return NULL;
}

template<class T>
TreeNode<T>* Tree<T>::NextBrother(TreeNode<T>* p)
{
	if (p != NULL && (p->GetNextBrother()) != NULL)
		return p->GetNextBrother();
	return NULL;
}

/*递归先根遍历以t为根指针的树*/
template<class T>
void Tree<T>::PreOrder(TreeNode<T>* t)
{
	if (t != NULL)
	{
		//访问结点t
		cout << t->GetData() << endl;
		TreeNode<T>* child = FirstChild(t);
		while (child)
		{
			PreOrder(child);
			child = NextBrother(child);
		}
	}
}

/*非递归先根遍历以t为根指针的树*/
template<class T>
void Tree<T>::NorecPreOrder(TreeNode<T>* t)
{
	if (t == NULL)
		return;
	arrayStack<TreeNode<T>*> s;
	TreeNode<T>* p = t;
	while (!s.empty())
	{
		while (p != NULL)
		{
			cout << p->GetData() << endl;
			s.push(p);
			p = FirstChild(p);
		}
		while (p == NULL && !s.empty())
		{
			p = s.top();
			s.pop();
			p = NextBrother(p);
		}
	}
}

/*按层次次序遍历以当前结点为根的树，利用辅助队列*/
template<class T>
void Tree<T>::LevelOrder(TreeNode<T>* t)
{
	arrayQueue<TreeNode<T>*> q;
	if (t != NULL)
	{
		TreeNode<T>* p;
		q.push(t);
		while (!q.empty())
		{
			p = q.front();
			q.pop();
			cout << p->GetData() << endl;
			p = FirstChild(p);
			while (p != NULL)
			{
				q.push(p);
				p = NextBrother(p);
			}
		}
	}
}

/*在以t为根节点的树中，搜索p的父节点*/
template<class T>
TreeNode<T>* Tree<T>::FindFather(TreeNode<T>* t, TreeNode<T>* p)
{
	if (t == NULL || p == NULL || p == t)
		return NULL;
	TreeNode<T>* result = NULL;
	TreeNode<T>* q = t->GetFirstChild();
	while (q != NULL)
	{
		if (q == p)
		{
			result = t;
			return result;
		}
		result = FindFather(q, p);
		if (result != NULL)
			return result;
		q = NextBrother(q);
	}
}

template<class T>
TreeNode<T>* Tree<T>::FindTarget(TreeNode<T>* t, T target)
{
	if (t == NULL)
		return NULL;
	TreeNode<T>* result = NULL;
	if ((t->GetData()) == target)
		return t;
	else
	{
		TreeNode<T>* p = t->GetFirstChild();
		while (p != NULL && (result = FindTarget(p, target)) == NULL)
			p = p->GetNextBrother();
		return result;
	}
}

/*删除以p为根的子树*/
template<class T>
void Tree<T>::Del(TreeNode<T>* p)
{
	if (p != NULL)
	{
		TreeNode<T>* q = p->GetFirstChild, * next;
		while (q != NULL)
		{
			next = q->GetNextBrother();
			Del(q);
			q = next;
		}
		delete p;
	}
}

/*在以t为根的树中删除根为p的子树*/
template<class T>
void Tree<T>::DelSubtree(TreeNode<T>* t, TreeNode<T>* p)
{
	if (t != NULL && p != NULL)
	{
		TreeNode<T>* q = NULL, * result = NULL;
		result = FindFather(t, p);
		if (result)
		{
			if ((result->GetFirstChild()) == p)
			{
				result->SetFirstChild(p->GetNextBrother());
				Del(p);
				return;
			}
		}
		else
		{
			Del(p);
			return;
		}
	}
}
