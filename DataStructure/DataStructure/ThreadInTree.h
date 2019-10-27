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
	ThreadNode<T>* head;	//���������������ı�ͷ���
	T stop;
	ThreadNode<T>* pre;		//��������������������������

public:
	ThreadInTree()
	{
		head = new ThreadNode<T>();
		head->SetLeft(head);
		head->SetLThread(1);
		head->SetRight(head);
		head->SetRThread(0);
	}

	//�������������������и����е�һ�����
	ThreadNode<T>* FIO(ThreadNode<T>* t);

	//�������������������и��������һ�����
	ThreadNode<T>* LIO(ThreadNode<T>* t);

	//����tΪ�����������������������������p���и�ǰ�����
	ThreadNode<T>* PIO(ThreadNode<T>* p);

	//����tΪ�����������������������������p���и���̽��
	ThreadNode<T>* NIO(ThreadNode<T>* p);

	//�и������Խ��tΪ���ڵ����������������
	void InOrderOf(ThreadNode<T>* t);

	//�и�������rootΪ���ڵ����������������
	void InOrder() { InOrderOf(GetRoot()); }

	//��������rootΪ���ڵ�Ķ�����
	void ThreadingTree();
	void InThreading(ThreadNode<T>* t);

	//����һ�����p,��Ϊ���s�����ӽڵ�
	void InsertRight(ThreadNode<T>* p, ThreadNode<T>* s);

	//����һ�����p,��Ϊ���s�����ӽڵ�
	void InsertLeft(ThreadNode<T>* p, ThreadNode<T>* s);

	//ɾ��s�����ӽڵ�
	void DeleteRight(ThreadNode<T>* s);

	//ɾ��s�����ӽڵ�
	void DeleteLeft(ThreadNode<T>* s);

	//��������
	ThreadNode<T>* GetRoot() { return head->GetLThread() == 0 ? head->GetLeft() : NULL; }
	void SetRoot(ThreadNode<T>* t) { head->SetLeft(t); head->SetLThread(t == NULL ? 1 : 0); }

	T GetStop() { return stop; }
	void SetStop(T tostop) { stop = tostop; }

	//������rootΪ���ڵ����������������
	void CreateThreadingTree(T tostop);
	//������rootΪ���ڵ����δ�����Ķ�����
	ThreadNode<T>* Create();

	//����t������������Ϊitem�Ľ��
	ThreadNode<T>* search(ThreadNode<T>* t, T item);
};

//FIO
//�����Խ��tΪ���ڵ�������������������и����еĵ�һ���ڵ�
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
//�����Խ��tΪ���ڵ�������������������и����е����һ�����
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
//��������tΪ��������������������p���и���̽��
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
//��������tΪ��������������������p���и�ǰ���ڵ�
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
//������p��Ϊ��������������T֮���s�����ӽڵ�
template<class T>
void ThreadInTree<T>::InsertRight(ThreadNode<T>* p, ThreadNode<T>* s)
{
	if (s == NULL || p == NULL)
		return;
	p->SetRight(s->GetRight());				//����	��ָ��
	p->SetRThread(s->GetRThread());			//����	������
	p->SetLeft(s);							//����	��ָ��
	p->SetLThread(1);						//����	������
	s->SetRight(p);							//����	��ָ��
	if (s->GetRThread() == 1)
	{
		s->SetRThread(0);					//����	������
		return;
	}
	else
	{
		ThreadNode<T>* q = p->GetRight();	//��������һ����������ָ��
		q = FIO(q);
		q->SetLeft(p);
		return;
	}
}

//InsertLeft
//������p��Ϊ��������������T֮���s�����ӽڵ�
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
//��������tΪ���ڵ�Ķ�����Ϊ��������������,��Ҫֱ��ʹ��
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
//ɾ�����s�����ӽڵ�p
template<class T>
void ThreadInTree<T>::DeleteRight(ThreadNode<T>* s)
{
	ThreadNode<T>* p, * t, * t1;
	if (s == NULL || s->GetRThread() == 1)
		return;
	p = s->GetRight();
	if (p->GetLThread() == 1 && p->GetRThread() == 1)		//Ҷ�ӽڵ�
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
		t1 = FIO(p->GetRight());			//��һ��
		t = LIO(p->GetLeft());				//���
		t->SetRight(p->GetRight());
		t->SetRThread(0);

		s->SetRight(p->GetLeft());
		t1->SetLeft(t);
	}
}