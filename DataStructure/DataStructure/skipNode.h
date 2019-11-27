#pragma once
#include <iostream>

using namespace std;

/*结构skipNode*/
template<class K,class E>
struct skipNode
{
	typedef pair<class K, class E> pairType;

	pairType element;
	skipNode<K, E>** next;

	skipNode(const pairType& thePair, int size)
		:element(thePair)
	{
		//对于一个lev级链表数对，其size值应为lev + 1
		next = new skipNode<K, E>* [size];
	}
};
