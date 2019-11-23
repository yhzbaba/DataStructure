#pragma once
#include <iostream>
#include "arrayStack.h"
#include "arrayQueue.h"

using namespace std;

//��������ֵ�


/*���ڵ���TreeNode����*/
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

/*����Tree������*/
template<class T>
class Tree
{
private:
	TreeNode<T>* root;			//���ڵ�
	T stop;
public:
	Tree() { root = NULL; }
	//���ؽ��p�Ĵ���ӽ��
	TreeNode<T>* FirstChild(TreeNode<T>* p);

	//���ؽ��p����һ���ֵܽ��
	TreeNode<T>* NextBrother(TreeNode<T>* p);


	//�ȸ�������tΪ���ڵ����
	void PreOrder(TreeNode<T>* p);
	
	//�ǵݹ��ȸ�������tΪ���ڵ����
	void NorecPreOrder(TreeNode<T>* t);

	//��α�����tΪ���ڵ����
	void LevelOrder(TreeNode<T>* t);

	//����tΪ���ڵ����������ֵΪtarget�Ľ��
	TreeNode<T>* FindTarget(TreeNode<T>* t, T target);

	//����t������p�ĸ��ڵ�
	TreeNode<T>* FindFather(TreeNode<T>* t, TreeNode<T>* p);

	//����tΪ��������ɾ����pΪ��������
	void DelSubtree(TreeNode<T>* t, TreeNode<T>* p);
	void Del(TreeNode<T>* p);


	//��������
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

/*�ݹ��ȸ�������tΪ��ָ�����*/
template<class T>
void Tree<T>::PreOrder(TreeNode<T>* t)
{
	if (t != NULL)
	{
		//���ʽ��t
		cout << t->GetData() << endl;
		TreeNode<T>* child = FirstChild(t);
		while (child)
		{
			PreOrder(child);
			child = NextBrother(child);
		}
	}
}

/*�ǵݹ��ȸ�������tΪ��ָ�����*/
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

/*����δ�������Ե�ǰ���Ϊ�����������ø�������*/
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

/*����tΪ���ڵ�����У�����p�ĸ��ڵ�*/
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

/*ɾ����pΪ��������*/
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

/*����tΪ��������ɾ����Ϊp������*/
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
