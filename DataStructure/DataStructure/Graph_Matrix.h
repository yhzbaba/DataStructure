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
	int graphSize;
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
	//���ͼ�Ĺؼ�·��
	//����Ȩͼ����ָ�����㵽�������ж�������·��
	//����Ȩͼ����ָ�����㵽�������ж�������·��
	//����Ȩͼ����ÿ�Զ�������̾���
	//����ͼ����С֧����������ķ�㷨
};

Graph_Matrix::Graph_Matrix()
{
	cout << "Please input the size of the graph." << endl;
	cin >> graphSize;

}

