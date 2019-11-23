#pragma once
#include "dictionary.h"
#include "pairNode.h"
#include <iostream>

using namespace std;

template<class K,class E>
class sortedChain :public dictionary<K, E>
{
public:
	sortedChain() { firstNode = NULL; dSize = 0; }
	~sortedChain();

	bool empty() const { return dSize == 0; }
	int size() const { return dSize; }
	pair<const K, E>* find(const K&) const;
	void erase(const K&);
	void insert(const pair<const K, E>&);
	void output(ostream& out) const;
protected:
	pairNode<K, E>* firstNode;
	int dSize;
};

/*destructor which deletes all nodes*/
template<class K,class E>
sortedChain<K, E>::~sortedChain()
{
	while (firstNode != NULL)
	{
		pairNode<K, E>* nextNode = firstNode->next;
		delete firstNode;
		firstNode = nextNode;
	}
}

/*return pointer to matching pair.*/
template<class K,class E>
pair<const K, E>* sortedChain<K, E>::find(const K& theKey) const
{
	pairNode<K, E>* currentNode = firstNode;

	// search for match with the key
	while (currentNode != NULL && currentNode->element.first != theKey)
		currentNode = currentNode->next;

	// verify match
	if (currentNode != NULL && currentNode->element.first == theKey)
		return &currentNode->element;

	// no match
	return NULL;
}

/*Insert thePair into the dictionary.If exists,overwrite it.*/
template<class K,class E>
void sortedChain<K, E>::insert(const pair<const K, E>& thePair)
{
	// tp trails p
	pairNode<K, E>* p = firstNode,
		* tp = NULL;

	// move tp until thePair can be pushed after tp
	while (p != NULL && p->element.first < thePair.first)
	{
		tp = p;
		p = p->next;
	}

	// verify if there exists match
	if (p != NULL && p->element.first == thePair.first)
	{
		//overwrite the old element
		p->element.second = thePair.second;
		return;
	}

	// no match,create a new node for thePair
	pairNode<K, E>* newNode = new pairNode<K, E>(thePair, p);

	if (tp == NULL)
		firstNode = newNode;
	else
		tp->next = newNode;

	dSize++;
	return;
}
