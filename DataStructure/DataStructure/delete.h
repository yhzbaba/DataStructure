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
