#pragma once
#include <iostream>

using namespace std;

template<class T>
class Element
{
private:
	T key;
public:
	T GetKey() const { return key; }
	void SetKey(T key) { this->key = key; }
};

template<class T>
bool operator<(Element<T> e1, Element<T> e2)
{
	if (e1.GetKey() < e2.GetKey())
		return true;
	else
		return false;
}

template<class T>
bool operator>(Element<T> e1, Element<T> e2)
{
	if (e1.GetKey() > e2.GetKey())
		return true;
	else
		return false;
}
