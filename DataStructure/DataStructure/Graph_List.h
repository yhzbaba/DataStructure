#pragma once
#include <iostream>
#include "arrayStack.h"
#include "arrayQueue.h"

using namespace std;

const int MaxGraphSize = 256;
	//最大顶点个数
const int MaxWeight = 1000;
	//最大权值

//边结点的结构体
struct Edge
{
	friend class Graph_List;
	int VerAdj;
		//邻接顶点序号，从0开始编号
	int cost;
		//the cost of the edge
	Edge* link;
		//the pointer which point to the next node
};

//顶点表中结点的结构体
struct Vertex
{
	friend class Graph_List;
	int VerName;
		//顶点的名称
	Edge* adjacent;
		//边链表头指针
};

//采用邻接表存储的Graph_List类定义
class Graph_List
{
private:
	Vertex* Head;
		//顶点表头指针
	int graphsize;
		//图中当前顶点个数
public:
	Graph_List();
	virtual ~Graph_List();

	int GetWeight(const int& v1, const int& v2);
		//返回指定边的权值
	int GetNextNeighbor(const int v1, const int v2);
		//序号为v1的顶点相对于序号为v2的顶点的下一个邻接顶点序号
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

//构造函数
Graph_List::Graph_List()
{
	int e, from, to, weight;
	Head = new Vertex[MaxGraphSize];
	cout << "输入顶点个数" << endl;
	cin >> graphsize;		//输入顶点个数
	//初始化Head数组
	for (int i = 0; i < graphsize; i++)
	{
		Head[i].VerName = i;
		Head[i].adjacent = NULL;
	}
	
	//输入边的个数
	cout << "输入边个数" << endl;
	cin >> e;

	//依次输入各边
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

//析构函数
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

//迭代深度优先搜索
void Graph_List::DDepthFirstSearch(const int v)
{
	int* visited = new int[graphsize];
	for (int k = 0; k < graphsize; k++)
	{
		visited[k] = 0;
	}
	arrayStack<int> S;
	S.push(v);	//将起始顶点压入栈
	int w;
	while (!S.empty())
	{
		w = S.top();
		S.pop();
		if (visited[w] == 0)
		{
			//w没有被访问过
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

//广度优先搜索
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

//拓扑排序
void Graph_List::TopoOrder()
{
	int n = graphsize;
	int* count = new int[n];
	//计算count数组
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
	int top = -1;			//初始化栈顶指针

	//将入度为0的点压栈
	for (int i = 0; i < n; i++)
	{
		if (count[i] == 0)
		{
			count[i] = top;
			top = i;
		}
	}

	//AOV网中最多有n个顶点
	for (int i = 0; i < n; i++)
	{
		//若循环体并未执行n次，栈顶指针已经为-1，说明有回路，直接返回
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

//关键路径
void Graph_List::CriticalPath()
{
	int i, k, e, l;
	int n = graphsize;
	int* ve = new int[n];			//事件的最早发生时间
	int* vl = new int[n];			//事件的最迟发生时间

	//初始化数组ve[]
	for (i = 0; i < n; i++)
	{
		ve[i] = 0;
	}

	//按拓扑顺序计算各事件允许的最早发生时间
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

	//数组vl[]初始化
	for (i = 0; i < n; i++)
		vl[i] = ve[n - 1];
	
	//逆序计算事件的最迟发生时间
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

	//求诸活动的最早开始时间和最迟开始时间
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

//无权最短路径
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
		//p为u的边链表的头指针
		p = Head[u].adjacent;
		//将u的未访问的邻接顶点入队，修改其path和dist值
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

//正权最短路径
void Graph_List::DShortestPath(const int v)
{
	int u, k;
	int max = 10000;
	Edge* p;
	int n = graphsize;
	int* path = new int[graphsize];
	int* dist = new int[graphsize];
	int* s = new int[n];				//记录i是否被访问过
	for (int i = 0; i < n; i++)
	{
		path[i] = -1;
		dist[i] = max;
		s[i] = 0;
	}
	dist[v] = 0;
	s[v] = 1;
	p = Head[v].adjacent;
	u = v;								//u为即将访问的顶点
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

		//确定接下来访问的结点u
		int Idist = max;
		for (int i = 0; i < n; i++)
		{
			if (dist[i] < Idist && s[i] == 0)
			{
				Idist = dist[i];
				u = i;
			}
		}
		s[u] = 1;		//访问u
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

//Prim算法