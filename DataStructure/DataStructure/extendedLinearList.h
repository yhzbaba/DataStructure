#pragma once
#include "linearList.h"

template<class T>
class extendedLinearList :public linearList<T>
{
public:
	virtual ~extendedLinearList() {}
	virtual void clear() = 0;
	virtual void push_back(const T& theElement) = 0;
};
