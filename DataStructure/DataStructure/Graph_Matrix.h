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
	int graphSize;
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
	//输出图的关键路径
	//在无权图中求指定顶点到其他所有顶点的最短路径
	//在正权图中求指定顶点到其他所有顶点的最短路径
	//在正权图中求每对顶点间的最短距离
	//构造图的最小支撑树的普利姆算法
};

Graph_Matrix::Graph_Matrix()
{
	cout << "Please input the size of the graph." << endl;
	cin >> graphSize;

}

