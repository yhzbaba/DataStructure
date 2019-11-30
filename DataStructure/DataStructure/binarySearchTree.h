#pragma once
#include <iostream>

using namespace std;

template<class T>
class BinarySearchTreeNode
{
public:
	T data;
	BinarySearchTreeNode<T>* left;
	BinarySearchTreeNode<T>* right;
public:
	BinarySearchTreeNode(T data)
	{
		this->data = data;
		left = right = NULL;
	}
	BinarySearchTreeNode()
	{
		data = 0;
		left = right = NULL;
	}
};

template<class T>
BinarySearchTreeNode<T>* Find(BinarySearchTreeNode<T>* root, T data)
{
	// recursive
	/*if (root == NULL)
		return NULL;
	if (data < root->data)
		return Find(root->left, data);
	else if (data > root->data)
		return Find(root->right, data);
	return root;*/

	//iteration
	if (root == NULL)
		return NULL;
	while (root)
	{
		if (data == root->data)
			return root;
		else if (data > root->data)
			root = root->right;
		else
			root = root->left;
	}
	return NULL;
}

template<class T>
BinarySearchTreeNode<T>* FindMin(BinarySearchTreeNode<T>* root)
{
	//recursive
	/*if (root == NULL)
		return NULL;
	else if (root->left == NULL)
		return root;
	else
		return FindMin(root->left);*/

	//iteration
	if (root == NULL)
		return NULL;
	while (root->left != NULL)
		root = root->left;
	return root;
}

template<class T>
BinarySearchTreeNode<T>* FindMax(BinarySearchTreeNode<T>* root)
{
	if (root == NULL)
		return NULL;
	while (root->right != NULL)
		root = root->right;

	return root;
}

template<class T>
BinarySearchTreeNode<T>* Insert(BinarySearchTreeNode<T>* root, T data)
{
	if (root == NULL)
	{
		root = new BinarySearchTreeNode<T>();
		if (root == NULL)
		{
			cout << "Memory Error." << endl;
			return NULL;
		}
		else
		{
			root->data = data;
			root->left = root->right = NULL;
		}
	}
	else
	{
		if (data < root->data)
			root->left = Insert(root->left, data);
		else if (data > root->data)
			root->right = Insert(root->right, data);
	}
	return root;
}

/*visit函数*/
template<class T>
void visit(BinarySearchTreeNode<T>* x)
{
	cout << x->data << ' ';
}

//中序遍历
template<class T>
void inOrder(BinarySearchTreeNode<T>* t)
{
	if (t != NULL)
	{
		inOrder(t->left);
		visit(t);
		inOrder(t->right);
	}
}

template<class T>
BinarySearchTreeNode<T>* Delete(BinarySearchTreeNode<T>* root, int data)
{
	BinarySearchTreeNode<T>* temp;
	if (root == NULL)
		cout << "Element not there in tree.";
	else if (data < root->data)
		root->left = Delete(root->left, data);
	else if (data > root->data)
		root->right = Delete(root->right, data);
	else
	{
		/*查找元素*/
		if (root->left && root->right)
		{
			/*替换为左子树中的最大值*/
			temp = FindMax(root->left);
			root->data = temp->data;
			root->left = Delete(root->left, root->data);
		}
		else
		{
			//一个孩子
			temp = root;
			if (root->left == NULL)
				root = root->right;
			if (root->right == NULL)
				root = root->left;
			delete temp;
		}
	}
	return root;
}