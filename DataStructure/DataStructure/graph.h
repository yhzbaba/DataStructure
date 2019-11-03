#pragma once
#include "edge.h"
#include "vertexIterator.h"

template<class T>
class graph
{
public:
	virtual ~graph() {}

	//ADT method
	virtual int numberOfVertices() const = 0;
	virtual int numberOfEdges() const = 0;
	virtual bool existsEdge(int, int) const = 0;
	virtual void insertEdge(edge<T>*) = 0;
	virtual void eraseEdge(int, int) = 0;
	virtual int degree(int) const = 0;
	virtual int inDegree(int) const = 0;
	virtual int outDegree(int) const = 0;

	//当且仅当是有向图的时候，返回值是true
	virtual bool directed() const = 0;
	//当且仅当是加权图时返回值是true
	virtual bool weighted() const = 0;
	virtual vertexIterator<T>* iterator(int) = 0;
	virtual void output(ostream&) const = 0
};
