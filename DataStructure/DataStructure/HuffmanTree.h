#pragma once
#include <iostream>
using namespace std;


template<class T>
class HuffmanNode
{
private:
	HuffmanNode<T>* LLINK;
	HuffmanNode<T>* RLINK;
	T INFO;
	int weight;
public:
	Huffmannode() {}
	HuffmanNode<T>* GetLeft() const { return LLINK; }
	void SetLeft(HuffmanNode<T>* L) { LLINK = L; }
	HuffmanNode<T>* GetRight() const { return RLINK; }
	void SetRight(HuffmanNode<T>* R) { RLINK = R; }
	T& GetData() { return INFO; }
	void SetData(const T& item) { INFO = item; }
	int GetWeight() { return weight; }
	void SetWeight() { weight = w; }
};

template<class T>
class HuffmanTree
{
private:
	int m;		//Huffman树结点个数
	HuffmanNode<T>** H;		//Huffman树结点的数组
public:
	HuffmanTree() { m = 0; H = NULL; }
	void CreatHuffmanTree(T* data, int* weight, int n);

	HuffmanNode<T>* GetRoot() { return m == 0 ? NULL : H[m]; }
	void PreOrder(HuffmanNode<T>* t) const;
	void InOrder(HuffmanNode<T>* t) const;
};

template<class T>
void HuffmanTree<T>::CreatHuffmanTree(T* data, int* weight, int n)
{
	m = n;
	H = new HuffmanNode<T> * [m + 1];
	HuffmanNode<T>* p1, * p2, * p, * t;
	int i, j;
	for (i = 1; i <= m; i++)
	{
		H[i] = new HuffmanNode<T>();
		H[i]->SetData(data[i]);
		H[i]->SetWeight(weight[i]);
		H[i]->SetLeft(NULL);
		H[i]->SetRight(NULL);
	}
	for (i = 1; i < m; i++)
	{
		t = new HuffmanNode<T>();
		p1 = H[i];
		p2 = H[i + 1];
		t->SetWeight(p1->GetWeight() + p2->GetWeight());
		t->SetLeft(p1);
		t->SetRight(p2);
		p = t;
		j = i + 2;
		while (j <= m && p->(GetWeight() > H[j]->GetWeight()))
		{
			H[j - 1] = H[j];
			j = j + 1;
		}
		H[j - 1] = p;
	}
}