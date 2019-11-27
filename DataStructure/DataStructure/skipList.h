#pragma once
#include "skipNode.h"
#include <iostream>
#include <math.h>
#include <sstream>
#include <string>
#include "myException.h"
#include "dictionary.h"

using namespace std;

template<class K,class E>
class skipList : public dictionary<K, E>
{
public:
	skipList(K, int maxPairs = 10000, float prob = 0.5);
	~skipList();

	bool empty() const { return dSize == 0; }
	int size() const { return dSize; }
	pair<const K, E>* find(const K&) const;
	void erase(const K&);
	void insert(const pair<const K, E>&);
	void output(ostream& out) const;
protected:
	float cutOff;			//确定层数
	int level() const;		//产生随机层数
	skipNode<K, E>* search(const K&) const;
	int levels;				//最大的非空链表
	int dSize;				//字典的数对个数
	int maxLevel;			//允许的最大链表层数
	K tailKey;				//最大关键字
	skipNode<K, E>* headerNode;		//头节点指针
	skipNode<K, E>* tailNode;		//尾节点指针
	skipNode<K, E>** last;			//last[i]表示i层的最后节点
};

/*参数largeKey的值大于字典的任何数对的关键字，存储在尾节点
  参数maxPairs的值是字典数对个数的最大数。代码允许字典数对个数大于maxPairs，但不超过性能会更好。
  参数prob的值是i-1级链表数对同时也是i级链表数对的概率。*/
template<class K,class E>
skipList<K, E>::skipList(K largeKey, int maxPairs, float prob)
{
	cutOff = prob * RAND_MAX;
	maxLevel = (int)ceil(logf((float)maxPairs) / logf(1 / prob)) - 1;
	levels = 0;
	dSize = 0;
	tailKey = largeKey;

	// 生成头节点、尾节点和数组last
	pair<K, E> tailPair;
	tailPair.first = tailKey;
	headerNode = new skipNode<K, E>(tailPair, maxLevel + 1);
	tailNode = new skipNode<K, E>(tailPair, 0);
	last = new skipNode<K, E>* [maxLevel + 1];

	// 链表为空时，任意级链表中的头节点都指向尾节点
	for (int i = 0; i < maxLevel; i++)
		headerNode->next[i] = tailNode;
}

/*
	在写插入代码之前，不仅要编写级的分配函数，为新数对指定它所属的级链表
	而且要编写搜索函数search，以存储在每一级链表搜索时所遇到的最后一个结点的指针
*/

/*级的分配方法*/
template<class K,class E>
int skipList<K, E>::level() const
{
	//返回一个表示链表级的随机数，这个数不大于maxLevel
	int lev = 0;
	while (rand() <= cutOff)
		lev++;
	return (lev <= maxLevel) ? lev : maxLevel;
}

/*搜索并把在每一级链表搜索时所遇到的最后一个结点指针保存起来*/
template<class K,class E>
skipNode<K, E>* skipList<K, E>::search(const K& theKey) const
{
	//位置beforeNode是关键字为theKey的结点之前最右边的位置
	skipNode<K, E>* beforeNode = headerNode;
	for (int i = levels; i >= 0; i--)
	{
		while (beforeNode->next[i]->element.first < theKey)
			beforeNode = beforeNode->next[i];
		last[i] = beforeNode;
	}
	return beforeNode->next[0];
}

/*跳表插入*/
template<class K,class E>
void skipList<K, E>::insert(const pair<const K, E>& thePair)
{
	/*把数对thePair插入字典，覆盖其关键字相同的已存在的数对*/
	//关键字太大
	if (thePair.first >= tailKey)
	{
		ostringstream s;
		s << "Key = " << thePair.first << " must be < " << tailKey;
		throw illegalParameterValue(s.str());
	}

	//查看关键字为theKey的数对是否已经存在
	skipNode<K, E>* theNode = search(thePair.first);
	//若存在，更新该数对的值
	if (theNode->element.first == thePair.first)
	{
		theNode->element.second = thePair.second;
		return;
	}

	//若不存在，确定新节点所在的级链表
	int theLevel = level();
	if (theLevel > levels)
	{
		theLevel = ++levels;
		last[theLevel] = headerNode;
	}

	//在节点theNode之后插入新节点
	skipNode<K, E>* newNode = new skipNode<K, E>(thePair, theLevel + 1);
	for (int i = 0; i < theLevel; i++)
	{
		newNode->next[i] = last[i]->next[i];
		last[i]->next[i] = newNode;
	}

	dSize++;
	return;
}

template<class K, class E>
void skipList<K, E>::output(ostream& out) const
{
	for (skipNode<K, E>* currentNode = headerNode->next[0];
		currentNode != tailNode;
		currentNode = currentNode->next[0])
		out << currentNode->element.first << " "
		<< currentNode->element.second << "  ";
}

/*find从最高级链表(即levels级链表,它只有一个数对)???不明白啊???开始查找*/
template<class K,class E>
pair<const K, E>* skipList<K, E>::find(const K& theKey) const
{
	if (theKey >= tailKey)
		return NULL;
	
	//位置beforeNode是关键字为theKey的节点之前最右边的位置
	skipNode<K, E>* beforeNode = headerNode;
	for (int i = levels; i >= 0; i--)
	{
		while (beforeNode->next[i]->element.first < theKey)
		{
			beforeNode = beforeNode->next[i];
		}
	}

	if (beforeNode->next[0]->element.first == theKey)
		return &beforeNode->next[0]->element;

	return NULL;
}

/*删除跳表的记录*/
template<class K,class E>
void skipList<K, E>::erase(const K& theKey)
{
	if (theKey >= tailKey)
	{
		reutrn;
	}

	//查看是否有匹配的数对
	skipNode<K, E>* theNode = search(theKey);
	if (theNode->element.first != theKey)
		return;

	for (int i = 0; i < levels && last[i]->next[i] == theNode; i++)
	{
		last[i]->next[i] = theNode->next[i];
	}

	//更新链表级
	while (levels > 0 && headerNode->next[levels] == tailNode)
		levels--;

	delete theNode;
	dSize--;
}

/*overload <<*/
template<class K,class E>
ostream& operator<<(ostream& out, const skipList<K, E>& x)
{
	x.output(out);
	return out;
}

template<class K, class E>
skipList<K, E>::~skipList()
{
	skipNode<K, E>* nextNode;
	while (headerNode != tailNode)
	{
		nextNode = headerNode->next[0];
		delete headerNode;
		headerNode = nextNode;
	}
	delete tailNode;
	delete[] last;
}