#pragma once
#include <iostream>
using namespace std;
//邻接矩阵存储的图

//图的最大顶点个数
const int MaxGraphSize = 256;

//图中允许的最大权值
const int MaxWeight = 100;

class Graph_Matrix
{
private:
	//邻接矩阵
	int edge[MaxGraphSize][MaxGraphSize];
	//当前图中顶点个数
	int graphsize;
public:
	//图的构造函数和析构函数
	Graph_Matrix();
	virtual ~Graph_Matrix();

	//图的维护函数
	//检测图是否为空
	int GraphEmpty(void) const;
	//检测图中顶点个数是否超过规定的上界
	int GraphFull(void) const;
	//返回图的顶点个数
	int NumberOfVertices(void) const;
	//返回图的边个数
	int NumberOfEdges() const;
	//返回指定边的权值
	int GetWeight(const int& v1, const int& v2);
	//返回顶点v的邻接顶点表
	int*& GetNeighbors(const int& v);
	//返回序号为v的顶点的第一个邻接顶点的序号
	int GetFirstNeighbor(const int v);
	//插入一个顶点
	void InsertVertex(const int& v);
	//插入一条边
	void InsertEdge(const int& v1, const int& v2, int weight);
	//删除一个顶点
	void DeleteVertex(const int& v);
	//删除一条边
	void DeleteEdge(const int& v1, const int& v2);

	//图的基本算法
	//递归DFS
	void DepthFirstSearch();
	//迭代DFS
	void DFS(const int v);
	//从顶点v开始进行的图的广度优先搜索
	void BFS(const int v);
	//输出图的拓扑排序
	void TopoOrder();
	//输出图的关键路径
	void CriticalPath();
	//在无权图中求指定顶点到其他所有顶点的最短路径
	void ShortestPath(const int v);
	//在正权图中求指定顶点到其他所有顶点的最短路径
	void DShortestPath(const int v);
	//在正权图中求每对顶点间的最短距离
	void AllLength();
	//构造图的最小支撑树的普利姆算法
	void Prim();
};

Graph_Matrix::Graph_Matrix()
{
	cout << "输入图的大小" << endl;
	cin >> graphsize;
	for (int i = 0; i < graphsize; i++)
		for (int j = 0; i < graphsize; j++)
			cin >> edge[i][i];
}

int Graph_Matrix::GetFirstNeighbor(const int v)
{
	if (v == -1)
		return -1;
	for (int i = 0; i < graphsize; i++)
		if (edge[v][i] > 0 && edge[v][i] < MaxWeight)
			return i;
	return -1;		//v没有邻接顶点，返回-1
}

//Prim算法
void Graph_Matrix::Prim()
{
	int n = graphsize;
	struct LV
	{
		int Lowcost;
		int Vex;
	}*closedge = new LV[n];
	struct Edge
	{
		int head;
		int tail;
		int cost;
	}*TE = new Edge[n - 1];

	//初始化邻接矩阵
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			if (edge[i][j] == 0)
				edge[i][j] = MaxWeight;
	//以顶点0为初始顶点，初始化数组closedge
	for (int i = 0; i < n; i++)
	{
		closedge[i].Lowcost = edge[0][i];
		closedge[i].Vex = 0;
	}
	//顶点0进入集合U
	closedge[0].Vex = -1;
	int count = 0;		//支撑树边计数器count
	//循环n-1次
	for (int i = 1; i < n; i++)
	{
		int min = MaxWeight + 1;	//设置最小值min
		int v = 0;
		for (int j = 0; j < n; j++)
		{
			if (closedge[j].Vex != -1 && closedge[j].Lowcost < min)
			{
				v = j;
				min = closedge[j].Lowcost;
			}
		}
		if (v != 0)
		{
			//向支撑树的边集合TE中添加一个边
			TE[count].head = closedge[v].Vex;
			TE[count].tail = v;
			TE[count].cost = closedge[v].Lowcost;
			count++;
			closedge[v].Lowcost = 0;	//修改域值
			closedge[v].Vex = -1;		//v进入U
			//因为v的进入，要修改一些值
			for (int j = 0; j < n; j++)
			{
				if (closedge[j].Vex != -1 && edge[v][j] < closedge[j].Lowcost)
				{
					closedge[j].Lowcost = edge[v][j];
					closedge[j].Vex = v;
				}
			}
		}
	}
	for (int i = 0; i < n - 1; i++)
	{
		cout << "(" << TE[i].head << ","
			<< TE[i].tail << "," << TE[i].cost << ")" << endl;
	}
	delete[] closedge;
	delete[] TE;
}


