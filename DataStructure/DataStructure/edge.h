#pragma once

using namespace std;

template<class T>
class edge
{
public:
	virtual ~edge() {}
	virtual int vertex1() const = 0;
			//Return the first vertex
	virtual int vertex2() const = 0;
			//Return the second vertex
	virtual T weight() const = 0;
			//Return the weight
};
