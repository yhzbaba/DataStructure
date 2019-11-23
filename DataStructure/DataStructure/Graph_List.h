#pragma once
#include <iostream>
#include "arrayStack.h"
#include "arrayQueue.h"

using namespace std;

const int MaxGraphSize = 256;
	//��󶥵����
const int MaxWeight = 1000;
	//���Ȩֵ

//�߽��Ľṹ��
struct Edge
{
	friend class Graph_List;
	int VerAdj;
		//�ڽӶ�����ţ���0��ʼ���
	int cost;
		//the cost of the edge
	Edge* link;
		//the pointer which point to the next node
};

//������н��Ľṹ��
struct Vertex
{
	friend class Graph_List;
	int VerName;
		//���������
	Edge* adjacent;
		//������ͷָ��
};

//�����ڽӱ�洢��Graph_List�ඨ��
class Graph_List
{
private:
	Vertex* Head;
		//�����ͷָ��
	int graphsize;
		//ͼ�е�ǰ�������
public:
	Graph_List();
	virtual ~Graph_List();

	int GetWeight(const int& v1, const int& v2);
		//����ָ���ߵ�Ȩֵ
	int GetNextNeighbor(const int v1, const int v2);
		//���Ϊv1�Ķ�����������Ϊv2�Ķ������һ���ڽӶ������
	void DepthFirstSearch();
	void DepthFirstSearch(const int v, int* visited);
	void DDepthFirstSearch(const int v);

	void BFS(const int s);

	void TopoOrder();

	void CriticalPath();

	void ShortestPath(const int v);

	void DShortestPath(const int v);

	void Prim();
};

//���캯��
Graph_List::Graph_List()
{
	int e, from, to, weight;
	Head = new Vertex[MaxGraphSize];
	cout << "���붥�����" << endl;
	cin >> graphsize;		//���붥�����
	//��ʼ��Head����
	for (int i = 0; i < graphsize; i++)
	{
		Head[i].VerName = i;
		Head[i].adjacent = NULL;
	}
	
	//����ߵĸ���
	cout << "����߸���" << endl;
	cin >> e;

	//�����������
	for (int i = 0; i < e; i++)
	{
		cin >> from >> to >> weight;
		Edge* p = new Edge;
		p->VerAdj = to;
		p->cost = weight;
		p->link = NULL;
		Edge* q = Head[from].adjacent;
		if (q == NULL)
			Head[from].adjacent = p;
		else
		{
			while (q->link != NULL)
				q = q->link;
			q->link = p;
		}
	}
}

//��������
Graph_List::~Graph_List()
{
	for (int i = 0; i < graphsize; i++)
	{
		Edge* p = Head[i].adjacent;
		while (p != NULL)
		{
			Head[i].adjacent = p->link;
			delete p;
			p = Head[i].adjacent;
		}
	}
	delete[] Head;
}

int Graph_List::GetWeight(const int& v1, const int& v2)
{
	if (v1 == -1 || v2 == -1)
		return 0;
	Edge* p = Head[v1].adjacent;
	while (p != NULL)
	{
		if (p->VerAdj == v2)
			return p->cost;
		p = p->link;
	}
	return 0;
}

int Graph_List::GetNextNeighbor(const int v1, const int v2)
{
	if (v1 != -1 && v2 != -1)
	{
		Edge* p = Head[v1].adjacent;
		while (p->VerAdj != v2 && p != NULL)
			p = p->link;
		if (p == NULL)
			return -1;
		p = p->link;
		if (p == NULL)
			return -1;
		return p->VerAdj;
	}
	return -1;
}

void Graph_List::DepthFirstSearch(const int v, int* visited)
{
	cout << v << " ";
	visited[v] = 1;
	Edge* p = Head[v].adjacent;
	while (p != NULL)
	{
		if (visited[p->VerAdj] != 1)
			DepthFirstSearch(p->VerAdj, visited);
		p = p->link;
	}
}

void Graph_List::DepthFirstSearch()
{
	int* visited = new int[graphsize];
	for (int k = 0; k < graphsize; k++)
		visited[k] = 0;
	DepthFirstSearch(0, visited);
	delete[] visited;
}

//���������������
void Graph_List::DDepthFirstSearch(const int v)
{
	int* visited = new int[graphsize];
	for (int k = 0; k < graphsize; k++)
	{
		visited[k] = 0;
	}
	arrayStack<int> S;
	S.push(v);	//����ʼ����ѹ��ջ
	int w;
	while (!S.empty())
	{
		w = S.top();
		S.pop();
		if (visited[w] == 0)
		{
			//wû�б����ʹ�
			cout << w << " ";
			visited[w] = 1;
			Edge* p = Head[w].adjacent;
			while (p != NULL)
			{
				if (visited[p->VerAdj] == 0)
					S.push(p->VerAdj);
				p = p->link;
			}
		}
	}
	delete[] visited;
}

//�����������
void Graph_List::BFS(const int s)
{
	int* visited = new int[graphsize];
	for (int k = 0; k < graphsize; k++)
	{
		visited[k] = 0;
	}
	cout << s << " ";
	visited[s] = 1;
	arrayQueue<int> q;
	q.push(s);
	while (!q.empty())
	{
		int v = q.front();
		Edge* p = Head[v].adjacent;
		while (p != NULL)
		{
			if (visited[p->VerAdj] == 0)
			{
				cout << p->VerAdj << " ";
				visited[p->VerAdj] = 1;
				q.push(p->VerAdj);
			}
			p = p->link;
		}
	}
	delete[] visited;
}

//��������
void Graph_List::TopoOrder()
{
	int n = graphsize;
	int* count = new int[n];
	//����count����
	for (int i = 0; i < n; i++)
		count[i] = 0;
	for (int i = 0; i < n; i++)
	{
		Edge* p = Head[i].adjacent;
		while (p != NULL)
		{
			count[p->VerAdj]++;
			p = p->link;
		}
	}
	int top = -1;			//��ʼ��ջ��ָ��

	//�����Ϊ0�ĵ�ѹջ
	for (int i = 0; i < n; i++)
	{
		if (count[i] == 0)
		{
			count[i] = top;
			top = i;
		}
	}

	//AOV���������n������
	for (int i = 0; i < n; i++)
	{
		//��ѭ���岢δִ��n�Σ�ջ��ָ���Ѿ�Ϊ-1��˵���л�·��ֱ�ӷ���
		if (top == -1)
		{
			cout << "There is a cycle in network!" << endl;
			return;
		}
		else
		{
			int j = top;
			top = count[top];
			cout << j << endl;
			Edge* p = Head[j].adjacent;
			while (p != NULL)
			{
				int k = p->VerAdj;
				count[k]--;
				if (count[k] == 0)
				{
					count[k] = top;
					top = k;
				}
				p = p->link;
			}
		}
	}
	delete[] count;
}

//�ؼ�·��
void Graph_List::CriticalPath()
{
	int i, k, e, l;
	int n = graphsize;
	int* ve = new int[n];			//�¼������緢��ʱ��
	int* vl = new int[n];			//�¼�����ٷ���ʱ��

	//��ʼ������ve[]
	for (i = 0; i < n; i++)
	{
		ve[i] = 0;
	}

	//������˳�������¼���������緢��ʱ��
	for (i = 0; i < n; i++)
	{
		Edge* p = Head[i].adjacent;
		while (p != NULL)
		{
			k = p->VerAdj;
			if (ve[i] + p->cost > ve[k])
				ve[k] = ve[i] + p->cost;
			p = p->link;
		}
	}

	//����vl[]��ʼ��
	for (i = 0; i < n; i++)
		vl[i] = ve[n - 1];
	
	//��������¼�����ٷ���ʱ��
	for (i = n - 2; i >= 0; i--)
	{
		Edge* p = Head[i].adjacent;
		while (p != NULL)
		{
			k = p->VerAdj;
			if (vl[k] - p->cost < vl[k])
				vl[k] = vl[k] - p->cost;
			p = p->link;
		}
	}

	//���������翪ʼʱ�����ٿ�ʼʱ��
	for (i = 0; i < n; i++)
	{
		Edge* p = Head[i].adjacent;
		while (p != NULL)
		{
			k = p->VerAdj;
			e = ve[i];
			l = vl[k] - p->cost;
			if (l == e)
				cout << "<" << i << "," << k << ">" << "is Critical Acitvity!" << endl;
			p = p->link;
		}
	}

	delete[] vl;
	delete[] ve;
}

//��Ȩ���·��
void Graph_List::ShortestPath(const int v)
{
	int u, k;
	Edge* p;
	int n = graphsize;
	int* path = new int[graphsize];
	int* dist = new int[graphsize];
	arrayQueue<int> Q;
	//the initialize of path and dist
	for (int i = 0; i < n; i++)
	{
		path[i] = -1;
		dist[i] = -1;
	}
	dist[v] = 0;
	Q.push(v);
	while (!Q.empty())
	{
		u = Q.front();
		Q.pop();
		//pΪu�ı������ͷָ��
		p = Head[u].adjacent;
		//��u��δ���ʵ��ڽӶ�����ӣ��޸���path��distֵ
		while (p != NULL)
		{
			k = p->VerAdj;
			if (dist[k] == -1)
			{
				Q.push(k);
				dist[k] = dist[u] + 1;
				path[k] = u;
			}
			p = p->link;
		}
	}
	for (int i = 0; i < n; i++)
		cout << path[i] << " ";
	cout << endl;
	for (int i = 0; i < n; i++)
		cout << dist[i] << " ";
	cout << endl;
	delete[] path;
	delete[] dist;
}

//��Ȩ���·��
void Graph_List::DShortestPath(const int v)
{
	int u, k;
	int max = 10000;
	Edge* p;
	int n = graphsize;
	int* path = new int[graphsize];
	int* dist = new int[graphsize];
	int* s = new int[n];				//��¼i�Ƿ񱻷��ʹ�
	for (int i = 0; i < n; i++)
	{
		path[i] = -1;
		dist[i] = max;
		s[i] = 0;
	}
	dist[v] = 0;
	s[v] = 1;
	p = Head[v].adjacent;
	u = v;								//uΪ�������ʵĶ���
	for (int j = 0; j < n; j++)
	{
		while (p != NULL)
		{
			k = p->VerAdj;
			if (s[k] != 1 && dist[u] + p->cost < dist[k])
			{
				dist[k] = dist[u] + p->cost;
				path[k] = u;
			}
			p = p->link;
		}

		//ȷ�����������ʵĽ��u
		int Idist = max;
		for (int i = 0; i < n; i++)
		{
			if (dist[i] < Idist && s[i] == 0)
			{
				Idist = dist[i];
				u = i;
			}
		}
		s[u] = 1;		//����u
		p = Head[u].adjacent;
	}
	for (int i = 0; i < n; i++)
	{
		cout << path[i] << " ";
	}
	cout << endl;
	for (int i = 0; i < n; i++)
	{
		cout << dist[i] << " ";
	}
	cout << endl;
	delete[] dist;
	delete[] path;
}

//Prim�㷨