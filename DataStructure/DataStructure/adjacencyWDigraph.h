#pragma once
#include "graph.h"
#include "myException.h"
#include "arrayQueue.h"
#include "make2dArray.h"
#include "weightedEdge.h"
#include "delete2dArray.h"
#include <iostream>
#include <iterator>

using namespace std;

template<class T>
class adjacencyWDigraph : public graph<T>
{
protected:
	int n;			// number of vertices
	int e;			// number of edges
	T** a;			// adjacency array
	T noEdge;		// denotes absent edge
public:
	// Constructor
	adjacencyWDigraph(int numberOfVertices = 0, T theNoEdge = 0)
	{
		// validate number of vertics
		if (numberOfVertices < 0)
			throw illegalParameterValue("number of vertics must be >= 0");
		n = numberOfVertices;
		e = 0;
		noEdge = theNoEdge;
		make2dArray(a, n + 1, n + 1);
		for (int i = 1; i <= n; i++)
			fill(a[i], a[i] + n + 1, noEdge);
	}

	~adjacencyWDigraph()
	{
		delete2dArray(a, n + 1);
	}

	int numberOfVertices() const { return n; }

	int numberOfEdges() const { return e; }

	bool directed() const { return true; }

	bool weighted() const { return true; }

	bool existsEdge(int i, int j) const
	{
		if (i<1 || j<1 || i>n || j>n || a[i][j] == noEdge)
			return false;
		else
			return true;
	}

	void insertEdge(edge<T>* theEdge)
	{
		int v1 = theEdge->vertex1();
		int v2 = theEdge->vertex2();
		if (v1<1 || v2<1 || v1>n || v2>n || v1 == v2)
		{
			cout << "INVALID." << endl;
			return;
		}

		if (a[v1][v2] == noEdge)
			e++;
		a[v1][v2] = theEdge->weight();
	}

	void eraseEdge(int i, int j)
	{
		if (i >= 1 && j >= 1 && i <= n && j <= n && a[i][j] != noEdge)
		{
			a[i][j] = noEdge;
			e--;
		}
	}

	void checkVertex(int theVertex) const
	{
		if (theVertex<1 || theVertex>n)
		{
			ostringstream s;
			s << "no vertex " << theVertex;
			throw illegalParameterValue(s.str());
		}
	}

	int degree(int theVertex) const
	{
		throw undefinedMethod("degree() undefined!");
	}

	int outDegree(int theVertex) const
	{
		checkVertex(theVertex);
		int sum = 0;
		for (int j = 1; j <= n; j++)
		{
			if (a[theVertex][j] != noEdge)
				sum++;
		}
		return sum;
	}

	int inDegree(int theVertex) const
	{
		checkVertex(theVertex);

		int sum = 0;
		for (int j = 1; j <= n; j++)
			if (a[j][theVertex] != noEdge)
				sum++;
		return sum;
	}

	class myIterator : public vertexIterator<T>
	{
	protected:
		T* row;
		T noEdge;
		int n;
		int currentVertex;
	public:
		myIterator(T* theRow, T theNoEdge, int numberOfVertices)
		{
			row = theRow;
			noEdge = theNoEdge;
			n = numberOfVertices;
			currentVertex = 1;
		}
		~myIterator() {}

		int next()
		{
			for (int j = currentVertex; j < n; j++)
			{
				if (row[j] != noEdge)
				{
					currentVertex = j + 1;
					return j;
				}
			}
			currentVertex = n + 1;
			return 0;
		}

		int next(T& theWeight)
		{
			for (int j = currentVertex; j <= n; j++)
			{
				if (row[j] != noEdge)
				{
					currentVertex = j + 1;
					theWeight = row[j];
					return j;
				}
			}
			currentVertex = n + 1;
			return 0;
		}
	};

	myIterator* iterator(int theVertex)
	{
		checkVertex(theVertex);
		return new myIterator(a[theVertex], noEdge, n);
	}

	void output(ostream& out) const
	{
		for (int i = 1; i <= n; i++)
		{
			copy(a[i] + 1, a[i] + n + 1, ostream_iterator<T>(out, " "));
			out << endl;
		}
	}

	void bfs(int v, int reach[], int label)
	{
		arrayQueue<int> q(10);
		reach[v] = label;
		q.push(v);
		while (!q.empty())
		{
			int w = q.front;
			q.pop();

			//��������ڽ��ڶ���w�Ļ�û�е���Ķ���
			for (int u = 1; u <= n; u++)
			{
				if (a[w][u] != noEdge && reach[u] == 0)
				{
					q.push(u);
					reach[u] = label;
				}
			}
		}
	}
};
