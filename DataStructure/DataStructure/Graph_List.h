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
	void DepthFirstSearch(const int v, int* visited);
	void DDepthFirstSearch(const int v);
	void BFS(const int s, int* visited);
public:
	Graph_List();
	virtual ~Graph_List();

	int GetWeight(const int& v1, const int& v2);
	//返回指定边的权值
	int GetNextNeighbor(const int v1, const int v2);
	//序号为v1的顶点相对于序号为v2的顶点的下一个邻接顶点序号

	void DepthFirstSearch();
	void BBFFSS();
	void TopoOrder();
	void CriticalPath();
	void ShortestPath(const int v);
	void DShortestPath(const int v);
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
		cout << "请输入第" << i + 1 << "条边:";
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
	for (int k = 0; k < graphsize; k++)
	{
		if (visited[k] == 0)
			DepthFirstSearch(k, visited);
	}
	delete[] visited;
}

void Graph_List::BBFFSS()
{
	int* visited = new int[graphsize];
	for (int k = 0; k < graphsize; k++)
		visited[k] = 0;
	for (int k = 0; k < graphsize; k++)
	{
		if (visited[k] == 0)
			BFS(k, visited);
	}
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
	for (int i = v + 1; i < graphsize; i++)
	{
		if (visited[i] == 0)
		{
			DDepthFirstSearch(i);
		}
		break;
	}
	delete[] visited;
}

//广度优先搜索
void Graph_List::BFS(const int s, int* visited)
{
	cout << s << " ";
	visited[s] = 1;
	arrayQueue<int> q;
	q.push(s);
	while (!q.empty())
	{
		int v = q.front();
		q.pop();
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
				cout << "<" << i << "," << k << ">" << "is Critical Activity!" << endl;
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

//n个顶点的无向简单图，最多多少条边?
//1+2+3+...+n-1=n(n-1)/2

//具有n个顶点E条边的图有多少种不同的邻接矩阵表示?
//n!

//检测给定图中是否存在从s到d的简单路径
namespace question_10 {
	struct Graph {
		int V;
		int E;
		int** adjMatrix;
	};

	int Visited[100] = { 0 };

	int HasSimplePath(struct Graph* G, int s, int d)
	{
		Visited[s] = 1;
		if (s == d)
			return 1;
		for (int t = 0; t < G->V; t++)
		{
			if (G->adjMatrix[s][t] && !Visited[t])
				if (HasSimplePath(G, t, d))
					return 1;
		}
		return 0;
	}
}

//计算G中有多少条从s到d的简单路径
//namespace question_10 {
//	int count = 0;
//	int Visited[100] = { 0 };
//	void CountSimplePaths(question_10::Graph* G, int s, int d) {
//		Visited[s] = 1;
//		if (s == d) {
//			count++;
//			Visited[s] = 0;
//			return;
//		}
//		for (int t = 0;t<G->V;t++)
//		{
//			if (G->adjMatrix[s][t] && !Visited[t]) {
//				CountSimplePaths(G, t, d);
//				Visited[t] = 0;
//			}
//		}
//	}
//}

namespace Dijkstra {
	int a[3010][3010] = { 0 }, d[3010] = { 0 }, n, m;
	bool v[3010];
	int path[3010];
	void dijkstra() {
		memset(d, 0x3f, sizeof(d));//dist数组
		memset(v, 0, sizeof(v));//节点标记
		memset(path, -1, sizeof(path));
		d[1] = 0;
		for (int i = 1; i < n; i++) {
			int x = 0;
			//找到未标记节点中dist最小的
			for (int j = 1; j <= n; j++) {
				if (!v[j] && (x == 0 || d[j] < d[x]))
					x = j;
			}
			v[x] = 1;
			//用全局最小值点x更新其他节点
			for (int y = 1; y <= n; y++) {
				if (d[x] + a[x][y] < d[y])
				{
					d[y] = d[x] + a[x][y];
					path[y] = x;
				}
			}
		}
	}

	void dijkstra_main() {
		cin >> Dijkstra::n >> Dijkstra::m;
		memset(Dijkstra::a, 0x3f, sizeof(a));
		for (int i = 1; i <= n; i++) a[i][i] = 0;
		for (int i = 1; i <= m; i++) {
			int x, y, z;
			scanf("%d%d%d", &x, &y, &z);
			a[x][y] = (a[x][y] < z) ? a[x][y] : z;
			a[y][x] = a[x][y];
		}

		dijkstra();
		for (int i = 1; i <= n; i++) {
			arrayStack<int> aStack;
			for (int j = i; j != path[1]; j = path[j])
				aStack.push(j);
			while (!aStack.empty())
			{
				printf("%d", aStack.top());
				aStack.pop();
				if (!aStack.empty())
					printf("->");
			}
			printf(" and the shortest value is %d\n", d[i]);
		}
	}
}

namespace SPFA {
	const int N = 100010, M = 1000010;
	int head[N] = { 0 }, ver[M] = { 0 }, edge[M], Next[M], d[N];
	int n, m, tot = 0;
	arrayQueue<int> q;
	bool v[N];

	void add(int x, int y, int z) {
		ver[++tot] = y, edge[tot] = z;
		Next[tot] = head[x], head[x] = tot;
	}

	void spfa() {
		memset(d, 0x3f, sizeof(d));
		memset(v, 0, sizeof(v));	//是否在队列中
		d[1] = 0; v[1] = 1;
		q.push(1);
		while (!q.empty())
		{
			//取出队头
			int x = q.front(); q.pop();
			v[x] = 0;
			//扫描所有出边
			for (int i = head[x]; i; i = Next[i]) {
				int y = ver[i], z = edge[i];
				if (d[y] > d[x] + z) {
					d[y] = d[x] + z;
					if (!v[y])
						q.push(y), v[y] = 1;
				}
			}
		}
	}

	void spfa_main() {
		cin >> SPFA::n >> SPFA::m;
		for (int i = 1; i <= m; i++) {
			int x, y, z;
			scanf("%d%d%d", &x, &y, &z);
			add(x, y, z);
		}

		spfa();
		for (int i = 1; i <= n; i++)
			printf("%d", d[i]);
	}
}

namespace Floyd {
	int d[310][310], n, m;
	void floyd_main() {
		cin >> Floyd::n >> Floyd::m;
		memset(d, 0x3f, sizeof(d));
		for (int i = 1; i <= n; i++) d[i][i] = 0;
		for (int i = 1; i <= m; i++) {
			int x, y, z;
			scanf("%d%d%d", &x, &y, &z);
			d[x][y] = (d[x][y] < z) ? d[x][y] : z;
			d[y][x] = d[x][y];
		}

		for (int k = 1; k <= n; k++)
			for (int i = 1; i <= n; i++)
				for (int j = 1; j <= n; j++)
					d[i][j] = d[i][j] < d[i][k] + d[k][j] ? d[i][j] : d[i][k] + d[k][j];

		for (int i = 0; i <= n; i++) {
			for (int j = 1; j <= n; j++)
				printf("%d ", d[i][j]);
			puts("\n");
		}
	}
}