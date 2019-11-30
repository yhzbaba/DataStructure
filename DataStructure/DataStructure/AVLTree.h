#pragma once
#include <iostream>

using namespace std;

template<class T>
class AVLTreeNode {
public:
	AVLTreeNode<T>* left;
	T data;
	AVLTreeNode<T>* right;
	int height;
};

template<class T>
int Height(AVLTreeNode<T>* root)
{
	if (!root)
		return -1;
	else
		return root->height;
}


