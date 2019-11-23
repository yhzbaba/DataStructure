#pragma once

using namespace std;

template<class K,class E>
struct pairNode
{
	typedef pair<const K, E> pairType;
	pairType element;
	pairNode<K, E>* next;
	pairNode(const pairType& thePair) :element(thePair) {}
	pairNode(const pairType& thePair, pairNode<K, E>* theNext)
		:element(thePair) {
		next = theNext;
	}
};
