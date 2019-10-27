#pragma once

template<class T>
class ThreadNode
{
private:
	int LThread, RThread;
	ThreadNode<T>* left;
	ThreadNode<T>* right;
	T data;
public:
	ThreadNode(const T item = 0) :data(item), left(NULL), right(NULL), LThread(0), RThread(0) {}
	
	ThreadNode<T>* GetLeft() const { return left; }
	void SetLeft(ThreadNode<T>* t) { left = t; }
	
	ThreadNode<T>* GetRight() const { return right; }
	void SetRight(ThreadNode<T>* t) { right = t; }
	
	T& GetData() { return data; }
	void SetData(const T& item) { data = item; }
	
	int GetLThread() { return LThread; }
	void SetLThread(const int d) { LThread = d; }
	
	int GetRThread() { return RThread; }
	void SetRThread(const int d) { RThread = d; }
};

template<class T>
class ThreadInTree
{
private:
	ThreadNode<T>* head;	//中序线索二叉树的表头结点
	T stop;
	ThreadNode<T>* pre;		//用于中序线索二叉树的线索化

public:
	ThreadInTree()
	{
		head = new ThreadNode<T>();
		head->SetLeft(head);
		head->SetLThread(1);
		head->SetRight(head);
		head->SetRThread(0);
	}

	//返回中序线索二叉树中根序列第一个结点
	ThreadNode<T>* FIO(ThreadNode<T>* t);

	//返回中序线索二叉树中根序列最后一个结点
	ThreadNode<T>* LIO(ThreadNode<T>* t);

	//在以t为根结点的中序线索二叉树中搜索结点p的中根前驱结点
	ThreadNode<T>* PIO(ThreadNode<T>* p);

	//在以t为根结点的中序线索二叉树中搜索结点p的中根后继结点
	ThreadNode<T>* NIO(ThreadNode<T>* p);

	//中根遍历以结点t为根节点的中序线索二叉树
	void InOrderOf(ThreadNode<T>* t);

	//中根遍历以root为根节点的中序线索二叉树
	void InOrder() { InOrderOf(GetRoot()); }

	//线索化以root为根节点的二叉树
	void ThreadingTree();
	void InThreading(ThreadNode<T>* t);

	//插入一个结点p,作为结点s的右子节点
	void InsertRight(ThreadNode<T>* p, ThreadNode<T>* s);

	//插入一个结点p,作为结点s的左子节点
	void InsertLeft(ThreadNode<T>* p, ThreadNode<T>* s);

	//删除s的右子节点
	void DeleteRight(ThreadNode<T>* s);

	//删除s的左子节点
	void DeleteLeft(ThreadNode<T>* s);

	//其他操作
	ThreadNode<T>* GetRoot() { return head->GetLThread() == 0 ? head->GetLeft() : NULL; }
	void SetRoot(ThreadNode<T>* t) { head->SetLeft(t); head->SetLThread(t == NULL ? 1 : 0); }

	T GetStop() { return stop; }
	void SetStop(T tostop) { stop = tostop; }

	//建立以root为根节点的中序线索二叉树
	void CreateThreadingTree(T tostop);
	//建立以root为根节点的尚未线索的二叉树
	ThreadNode<T>* Create();

	//在树t中搜索数据域为item的结点
	ThreadNode<T>* search(ThreadNode<T>* t, T item);
};

//FIO
//返回以结点t为根节点的中序线索二叉树的中根序列的第一个节点
template<class T>
ThreadNode<T>* ThreadInTree<T>::FIO(ThreadNode<T>* t)
{
	if (t == NULL)
		return NULL;
	ThreadNode<T>* q = t;
	while (q->GetLThread() == 0)
	{
		q = q->GetLeft();
	}
	return q;
}

//LIO
//返回以结点t为根节点的中序线索二叉树的中根序列的最后一个结点
template<class T>
ThreadNode<T>* ThreadInTree<T>::LIO(ThreadNode<T>* t)
{
	if (t == NULL)
		return NULL;
	ThreadNode<T>* q = t;
	while (q->GetRThread() == 0)
		q = q->GetRight();
	return q;
}

//NIO*
//搜索在以t为根的中序线索二叉树中p的中根后继结点
template<class T>
ThreadNode<T>* ThreadInTree<T>::NIO(ThreadNode<T>* p)
{
	if (p == NULL)
		return NULL;
	ThreadNode<T>* q = p->GetRight();
	if (p->GetRThread() == 1)
		return q;
	while (q->GetLThread() == 0)
		q = q->GetLeft();
	return q;
}

//PIO
//搜索在以t为根的中序线索二叉树中p的中根前驱节点
template<class T>
ThreadNode<T>* ThreadInTree<T>::PIO(ThreadNode<T>* p)
{
	if (p == NULL)
		return NULL;
	ThreadNode<T>* q = p->GetLeft();
	if (p->GetLThread() == 1)
		return q;
	while (q->GetRThread() == 0)
		q = q->GetRight();
	return q;
}

//InOrder*
template<class T>
void ThreadInTree<T>::InOrderOf(ThreadNode<T>* t)
{
	if (t == NULL)
		return;
	ThreadNode<T>* q;
	for (q = FIO(t); q != head; q = NIO(q))
	{
		cout << q->GetData() << endl;
	}
}

//InsertRight
//插入结点p作为中序线索二叉树T之结点s的右子节点
template<class T>
void ThreadInTree<T>::InsertRight(ThreadNode<T>* p, ThreadNode<T>* s)
{
	if (s == NULL || p == NULL)
		return;
	p->SetRight(s->GetRight());				//插入	右指针
	p->SetRThread(s->GetRThread());			//插入	右线索
	p->SetLeft(s);							//插入	左指针
	p->SetLThread(1);						//插入	左线索
	s->SetRight(p);							//被插	右指针
	if (s->GetRThread() == 1)
	{
		s->SetRThread(0);					//被插	右线索
		return;
	}
	else
	{
		ThreadNode<T>* q = p->GetRight();	//右子树第一个遍历的左指针
		q = FIO(q);
		q->SetLeft(p);
		return;
	}
}

//InsertLeft
//插入结点p作为中序线索二叉树T之结点s的左子节点
template<class T>
void ThreadInTree<T>::InsertLeft(ThreadNode<T>* insertNode, ThreadNode<T>* originNode)
{
	if (insertNode == NULL || originNode == NULL)
		return;
	insertNode->SetLeft(originNode->GetLeft());

	insertNode->SetLThread(originNode->GetLThread());

	originNode->SetLeft(insertNode);
	insertNode->SetRight(originNode);
	insertNode->SetRThread(1);

	if (originNode->GetLThread() == 1)
	{
		originNode->SetLThread(0);
		return;
	}
	else
	{
		ThreadNode<T>* q = originNode->GetLeft();
		q = LIO(q);
		q->SetRight(insertNode);
		return;
	}
}

//InThread
//线索化以t为根节点的二叉树为中序线索二叉树,不要直接使用
template<class T>
void ThreadInTree<T>::InThreading(ThreadNode<T>* t)
{
	if (t != NULL)
	{
		InThreading(t->GetLeft());
		if (t->GetLeft() == NULL)
		{
			t->SetLeft(pre);
			t->SetLThread(1);
		}
		if (pre != head && pre->GetRight() == NULL)
		{
			pre->SetRight(t);
			pre->SetRThread(1);
		}
		pre = t;
		InThreading(t->GetRight());
	}
}

template<class T>
void ThreadInTree<T>::ThreadingTree()
{
	pre = head;
	InThreading(GetRoot());
	if (pre != head)
	{
		pre->SetRight(head);
		pre->SetRThread(1);
	}
}

//DR
//删除结点s的右子节点p
template<class T>
void ThreadInTree<T>::DeleteRight(ThreadNode<T>* s)
{
	ThreadNode<T>* p, * t, * t1;
	if (s == NULL || s->GetRThread() == 1)
		return;
	p = s->GetRight();
	if (p->GetLThread() == 1 && p->GetRThread() == 1)		//叶子节点
	{
		s->SetRight(p->GetRight());
		s->SetRThread(p->GetRThread());
	}
	else if (p->GetLThread() == 1)
	{
		t = FIO(p->GetRight());
		s->SetRight(p->GetRight());
		t->SetLeft(s);
	}
	else if (p->GetRThread() == 1)
	{
		t = LIO(t);
		s->SetRight(p->GetLeft());
		t->SetRight(p->GetRight());
	}
	else
	{
		t1 = FIO(p->GetRight());			//第一个
		t = LIO(p->GetLeft());				//最后
		t->SetRight(p->GetRight());
		t->SetRThread(0);

		s->SetRight(p->GetLeft());
		t1->SetLeft(t);
	}
}