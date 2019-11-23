#pragma once
#include <iostream>
using namespace std;
//�ڽӾ���洢��ͼ

//ͼ����󶥵����
const int MaxGraphSize = 256;

//ͼ����������Ȩֵ
const int MaxWeight = 100;

class Graph_Matrix
{
private:
	//�ڽӾ���
	int edge[MaxGraphSize][MaxGraphSize];
	//��ǰͼ�ж������
	int graphsize;
public:
	//ͼ�Ĺ��캯������������
	Graph_Matrix();
	virtual ~Graph_Matrix();

	//ͼ��ά������
	//���ͼ�Ƿ�Ϊ��
	int GraphEmpty(void) const;
	//���ͼ�ж�������Ƿ񳬹��涨���Ͻ�
	int GraphFull(void) const;
	//����ͼ�Ķ������
	int NumberOfVertices(void) const;
	//����ͼ�ı߸���
	int NumberOfEdges() const;
	//����ָ���ߵ�Ȩֵ
	int GetWeight(const int& v1, const int& v2);
	//���ض���v���ڽӶ����
	int*& GetNeighbors(const int& v);
	//�������Ϊv�Ķ���ĵ�һ���ڽӶ�������
	int GetFirstNeighbor(const int v);
	//����һ������
	void InsertVertex(const int& v);
	//����һ����
	void InsertEdge(const int& v1, const int& v2, int weight);
	//ɾ��һ������
	void DeleteVertex(const int& v);
	//ɾ��һ����
	void DeleteEdge(const int& v1, const int& v2);

	//ͼ�Ļ����㷨
	//�ݹ�DFS
	void DepthFirstSearch();
	//����DFS
	void DFS(const int v);
	//�Ӷ���v��ʼ���е�ͼ�Ĺ����������
	void BFS(const int v);
	//���ͼ����������
	void TopoOrder();
	//���ͼ�Ĺؼ�·��
	void CriticalPath();
	//����Ȩͼ����ָ�����㵽�������ж�������·��
	void ShortestPath(const int v);
	//����Ȩͼ����ָ�����㵽�������ж�������·��
	void DShortestPath(const int v);
	//����Ȩͼ����ÿ�Զ�������̾���
	void AllLength();
	//����ͼ����С֧����������ķ�㷨
	void Prim();
};

Graph_Matrix::Graph_Matrix()
{
	cout << "����ͼ�Ĵ�С" << endl;
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
	return -1;		//vû���ڽӶ��㣬����-1
}

//Prim�㷨
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

	//��ʼ���ڽӾ���
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			if (edge[i][j] == 0)
				edge[i][j] = MaxWeight;
	//�Զ���0Ϊ��ʼ���㣬��ʼ������closedge
	for (int i = 0; i < n; i++)
	{
		closedge[i].Lowcost = edge[0][i];
		closedge[i].Vex = 0;
	}
	//����0���뼯��U
	closedge[0].Vex = -1;
	int count = 0;		//֧�����߼�����count
	//ѭ��n-1��
	for (int i = 1; i < n; i++)
	{
		int min = MaxWeight + 1;	//������Сֵmin
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
			//��֧�����ı߼���TE�����һ����
			TE[count].head = closedge[v].Vex;
			TE[count].tail = v;
			TE[count].cost = closedge[v].Lowcost;
			count++;
			closedge[v].Lowcost = 0;	//�޸���ֵ
			closedge[v].Vex = -1;		//v����U
			//��Ϊv�Ľ��룬Ҫ�޸�һЩֵ
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


