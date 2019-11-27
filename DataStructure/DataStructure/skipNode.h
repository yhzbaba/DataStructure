#pragma once
#include <iostream>

using namespace std;

/*�ṹskipNode*/
template<class K,class E>
struct skipNode
{
	typedef pair<class K, class E> pairType;

	pairType element;
	skipNode<K, E>** next;

	skipNode(const pairType& thePair, int size)
		:element(thePair)
	{
		//����һ��lev���������ԣ���sizeֵӦΪlev + 1
		next = new skipNode<K, E>* [size];
	}
};
