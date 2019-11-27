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
	float cutOff;			//ȷ������
	int level() const;		//�����������
	skipNode<K, E>* search(const K&) const;
	int levels;				//���ķǿ�����
	int dSize;				//�ֵ�����Ը���
	int maxLevel;			//���������������
	K tailKey;				//���ؼ���
	skipNode<K, E>* headerNode;		//ͷ�ڵ�ָ��
	skipNode<K, E>* tailNode;		//β�ڵ�ָ��
	skipNode<K, E>** last;			//last[i]��ʾi������ڵ�
};

/*����largeKey��ֵ�����ֵ���κ����ԵĹؼ��֣��洢��β�ڵ�
  ����maxPairs��ֵ���ֵ����Ը���������������������ֵ����Ը�������maxPairs�������������ܻ���á�
  ����prob��ֵ��i-1����������ͬʱҲ��i���������Եĸ��ʡ�*/
template<class K,class E>
skipList<K, E>::skipList(K largeKey, int maxPairs, float prob)
{
	cutOff = prob * RAND_MAX;
	maxLevel = (int)ceil(logf((float)maxPairs) / logf(1 / prob)) - 1;
	levels = 0;
	dSize = 0;
	tailKey = largeKey;

	// ����ͷ�ڵ㡢β�ڵ������last
	pair<K, E> tailPair;
	tailPair.first = tailKey;
	headerNode = new skipNode<K, E>(tailPair, maxLevel + 1);
	tailNode = new skipNode<K, E>(tailPair, 0);
	last = new skipNode<K, E>* [maxLevel + 1];

	// ����Ϊ��ʱ�����⼶�����е�ͷ�ڵ㶼ָ��β�ڵ�
	for (int i = 0; i < maxLevel; i++)
		headerNode->next[i] = tailNode;
}

/*
	��д�������֮ǰ������Ҫ��д���ķ��亯����Ϊ������ָ���������ļ�����
	����Ҫ��д��������search���Դ洢��ÿһ����������ʱ�����������һ������ָ��
*/

/*���ķ��䷽��*/
template<class K,class E>
int skipList<K, E>::level() const
{
	//����һ����ʾ������������������������maxLevel
	int lev = 0;
	while (rand() <= cutOff)
		lev++;
	return (lev <= maxLevel) ? lev : maxLevel;
}

/*����������ÿһ����������ʱ�����������һ�����ָ�뱣������*/
template<class K,class E>
skipNode<K, E>* skipList<K, E>::search(const K& theKey) const
{
	//λ��beforeNode�ǹؼ���ΪtheKey�Ľ��֮ǰ���ұߵ�λ��
	skipNode<K, E>* beforeNode = headerNode;
	for (int i = levels; i >= 0; i--)
	{
		while (beforeNode->next[i]->element.first < theKey)
			beforeNode = beforeNode->next[i];
		last[i] = beforeNode;
	}
	return beforeNode->next[0];
}

/*�������*/
template<class K,class E>
void skipList<K, E>::insert(const pair<const K, E>& thePair)
{
	/*������thePair�����ֵ䣬������ؼ�����ͬ���Ѵ��ڵ�����*/
	//�ؼ���̫��
	if (thePair.first >= tailKey)
	{
		ostringstream s;
		s << "Key = " << thePair.first << " must be < " << tailKey;
		throw illegalParameterValue(s.str());
	}

	//�鿴�ؼ���ΪtheKey�������Ƿ��Ѿ�����
	skipNode<K, E>* theNode = search(thePair.first);
	//�����ڣ����¸����Ե�ֵ
	if (theNode->element.first == thePair.first)
	{
		theNode->element.second = thePair.second;
		return;
	}

	//�������ڣ�ȷ���½ڵ����ڵļ�����
	int theLevel = level();
	if (theLevel > levels)
	{
		theLevel = ++levels;
		last[theLevel] = headerNode;
	}

	//�ڽڵ�theNode֮������½ڵ�
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

/*find����߼�����(��levels������,��ֻ��һ������)???�����װ�???��ʼ����*/
template<class K,class E>
pair<const K, E>* skipList<K, E>::find(const K& theKey) const
{
	if (theKey >= tailKey)
		return NULL;
	
	//λ��beforeNode�ǹؼ���ΪtheKey�Ľڵ�֮ǰ���ұߵ�λ��
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

/*ɾ������ļ�¼*/
template<class K,class E>
void skipList<K, E>::erase(const K& theKey)
{
	if (theKey >= tailKey)
	{
		reutrn;
	}

	//�鿴�Ƿ���ƥ�������
	skipNode<K, E>* theNode = search(theKey);
	if (theNode->element.first != theKey)
		return;

	for (int i = 0; i < levels && last[i]->next[i] == theNode; i++)
	{
		last[i]->next[i] = theNode->next[i];
	}

	//��������
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