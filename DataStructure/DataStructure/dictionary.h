#pragma once
#include <iostream>

using namespace std;

/*≥ÈœÛ¿‡dictionary*/
template<class K,class E>
class dictionary
{
public:
	virtual ~dictionary() {}
	virtual bool empty() const = 0;
	virtual int size() const = 0;
	virtual pair<const K, E>* find(const K&) const = 0;
	virtual void erase(const K&) = 0;
	virtual void insert(const pair<const K, E>&) = 0;
};
