#pragma once
#include <iostream>
using namespace std;

template<class T>
class Element
{
public:
	T GetKey()const { return key; }
	void SetKey(T k) { key = k; }
private:
	T key;
};
