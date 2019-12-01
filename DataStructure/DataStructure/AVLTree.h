#pragma once
#include <iostream>
#include <math.h>

using namespace std;
//cyberchef

template<class T>
class AVLTreeNode {
public:
	T key;				// the key
	int height;			// the height
	AVLTreeNode<T>* left;
	AVLTreeNode<T>* right;
	AVLTreeNode(T value, AVLTreeNode<T>* l, AVLTreeNode<T>* r) :
		key(value), left(l), right(r) {
		height = 0;
	}
};

template<class T>
class AVLTree
{
private:
	AVLTreeNode<T>* root;			// the root node
public:
	AVLTree() :root(NULL) {}
	~AVLTree() { destroy(root); }

	// get the height of the tree
	int height();
	// compare the value of the two parameters
	int max(T a, T b);

	void inOrder();

	AVLTreeNode<T>* search(T key);
	AVLTreeNode<T>* iterativeSearch(T key);

	// search the maximum and the minimum
	T minimum();
	T maximum();

	void insert(T key);
	void remove(T key);
	void destroy();
	//void print();
private:
	// inner interfaces
	int height(AVLTreeNode<T>* tree);
	void inOrder(AVLTreeNode<T>* tree) const;

	AVLTreeNode<T>* search(AVLTreeNode<T>* x, T key) const;
	AVLTreeNode<T>* iterativeSearch(AVLTreeNode<T>* x, T key) const;

	AVLTreeNode<T>* minimum(AVLTreeNode<T>* tree);
	AVLTreeNode<T>* maximum(AVLTreeNode<T>* tree);

	AVLTreeNode<T>* insert(AVLTreeNode<T>*& tree, T key);
	AVLTreeNode<T>* remove(AVLTreeNode<T>*& tree, AVLTreeNode<T>* z);

	void destroy(AVLTreeNode<T>*& tree);
	//void print(AVLTreeNode<T>* tree, T key, int direction);
	AVLTreeNode<T>* leftLeftRotation(AVLTreeNode<T>* k2);
	AVLTreeNode<T>* rightRightRotation(AVLTreeNode<T>* k1);
	AVLTreeNode<T>* leftRightRotation(AVLTreeNode<T>* k3);
	AVLTreeNode<T>* rightLeftRotation(AVLTreeNode<T>* k1);
};

template<class T>
int AVLTree<T>::height(AVLTreeNode<T>* tree)
{
	if (tree != NULL)
		return tree->height;
	return -1;
}

template<class T>
int AVLTree<T>::height()
{
	return height(root);
}

template<class T>
int AVLTree<T>::max(T a, T b)
{
	return a > b ? a : b;
}

/*The insert happens in the left child of the left child.*/
template<class T>
AVLTreeNode<T>* AVLTree<T>::leftLeftRotation(AVLTreeNode<T>* k2)
{
	AVLTreeNode<T>* k1;

	k1 = k2->left;
	k2->left = k1->right;
	k1->right = k2;

	k2->height = max(height(k2->left), height(k2->right)) + 1;
	k1->height = max(height(k1->left), k2->height) + 1;

	return k1;
}

/*The insert happens in the right child of the right child*/
template<class T>
AVLTreeNode<T>* AVLTree<T>::rightRightRotation(AVLTreeNode<T>* k1)
{
	AVLTreeNode<T>* k2;

	k2 = k1->right;
	k1->right = k2->left;
	k2->left = k1;

	k1->height = max(height(k1->right), height(k2->left)) + 1;
	k2->height = max(k1->height, height(k2->right)) + 1;

	return k2;
}

/*The insert happens in the right child of the left child*/
template<class T>
AVLTreeNode<T>* AVLTree<T>::leftRightRotation(AVLTreeNode<T>* k3)
{
	k3->left = rightRightRotation(k3->left);

	return leftLeftRotation(k3);
}

/*The insert happens in the left child of the right child*/
template<class T>
AVLTreeNode<T>* AVLTree<T>::rightLeftRotation(AVLTreeNode<T>* k1)
{
	k1->right = leftLeftRotation(k1->right);
	
	return rightRightRotation(k1);
}

template<class T>
AVLTreeNode<T>* AVLTree<T>::insert(AVLTreeNode<T>*& tree, T key)
{
	if (tree == NULL)
	{
		// build a new node
		tree = new AVLTreeNode<T>(key, NULL, NULL);
		if (tree == NULL)
		{
			cout << "ERROR: create avltree node failed!" << endl;
			return NULL;
		}
	}
	else if (key < tree->key)
	{
		tree->left = insert(tree->left, key);
		if (height(tree->left) - height(tree->right) == 2)
		{
			if (key < tree->left->key)
				tree = leftLeftRotation(tree);
			else
				tree = leftRightRotation(tree);
		}
	}
	else if (key > tree->key)
	{
		tree->right = insert(tree->right, key);
		if (height(tree->right) - height(tree->left) == 2)
		{
			if (key > tree->right->key)
				tree = rightRightRotation(tree);
			else
				tree = rightLeftRotation(tree);
		}
	}
	
	tree->height = max(height(tree->left), height(tree->right)) + 1;
	return tree;
}

template<class T>
void AVLTree<T>::insert(T key)
{
	insert(root, key);
}

template<class T>
AVLTreeNode<T>* AVLTree<T>::remove(AVLTreeNode<T>*& tree, AVLTreeNode<T>* z)
{
	if (tree == NULL || z == NULL)
		return NULL;
	if (z->key < tree->key)
	{
		tree->left = remove(tree->left, z);
		if (height(tree->right) - height(tree->left) == 2)
		{
			AVLTreeNode<T>* r = tree->right;
			if (height(r->left) > height(r->right))
				tree = rightLeftRotation(root);
			else
				tree = rightRightRotation(tree);
		}
	}
	else if (z->key > tree->key)
	{
		tree->right = remove(tree->right, z);
		if (height(tree->left) - height(tree->right) == 2)
		{
			AVLTreeNode<T>* r = tree->left;
			if (height(r->left) > height(r->right))
				tree = leftLeftRotation(tree);
			else
				tree = leftRightRotation(tree);
		}
	}
	else
	{
		// tree is the node to delete
		if (tree->left && tree->right)
		{
			if (height(tree->left) > height(tree->right))
			{
				AVLTreeNode<T>* max = maximum(tree->left);
				tree->key = max->key;
				tree->left = remove(tree->left, max);
			}
			else
			{
				AVLTreeNode<T>* min = minimum(tree->right);
				tree->key = min->key;
				tree->right = remove(tree->right, min);
			}
		}
		else
		{
			AVLTreeNode<T>* temp = tree;
			tree = (tree->left != NULL) ? tree->left : tree->right;
			delete temp;
		}
	}
	return tree;
}

template<class T>
void AVLTree<T>::remove(T key)
{
	AVLTreeNode<T>* z;
	if ((z = search(root, key)) != NULL)
		root = remove(root, z);
}

template<class T>
void AVLTree<T>::inOrder(AVLTreeNode<T>* t) const
{
	if (t != NULL)
	{
		inOrder(t->left);
		cout << t->key << " ";
		inOrder(t->right);
	}
}

template<class T>
void AVLTree<T>::inOrder()
{
	inOrder(root);
}

template<class T>
AVLTreeNode<T>* AVLTree<T>::search(AVLTreeNode<T>* x, T key) const
{
	if (x == NULL || x->key == key)
		return x;
	if (key < x->key)
		return search(x->left, key);
	else
		return search(x->right, key);
}

template<class T>
AVLTreeNode<T>* AVLTree<T>::search(T key)
{
	return search(root, key);
}

template<class T>
AVLTreeNode<T>* AVLTree<T>::iterativeSearch(AVLTreeNode<T>* x, T key) const
{
	while (x != NULL && x->key != key)
	{
		if (key < x->key)
			x = x->left;
		else
			x = x->right;
	}
	return x;
}

template<class T>
AVLTreeNode<T>* AVLTree<T>::iterativeSearch(T key)
{
	return iterativeSearch(root, key);
}

template<class T>
AVLTreeNode<T>* AVLTree<T>::minimum(AVLTreeNode<T>* tree)
{
	if (tree == NULL)
		return NULL;
	while (tree->left != NULL)
		tree = tree->left;
	return tree;
}

template<class T>
T AVLTree<T>::minimum()
{
	AVLTreeNode<T>* p = minimum(root);
	if (p != NULL)
		return p->key;
	return (T)NULL;
}

template<class T>
AVLTreeNode<T>* AVLTree<T>::maximum(AVLTreeNode<T>* tree)
{
	if (tree == NULL)
		return NULL;
	while (tree->right != NULL)
		tree = tree->right;
	return tree;
}

template<class T>
T AVLTree<T>::maximum()
{
	AVLTreeNode<T>* p = maximum(root);
	if (p != NULL)
		return p->key;
	return (T)NULL;
}

template<class T>
void AVLTree<T>::destroy(AVLTreeNode<T>*& tree)
{
	if (tree == NULL)
		return;
	if (tree->left != NULL)
		destroy(tree->left);
	if (tree->right != NULL)
		destroy(tree->right);
	delete tree;
}

template<class T>
void AVLTree<T>::destroy()
{
	destroy(root);
}

//template<class T>
//void AVLTree<T>::print(AVLTreeNode<T>* tree, T key, int direction)
//{
//	if (tree != NULL)
//	{
//		if (direction == 0)
//			cout << setw(2) << tree->key << "is root" << endl;
//		else
//			cout << setw(2) << tree->key << "is" << setw(2) << key << "'s" << setw(12)
//			<< (direction == 1 ? "right child" : "left child") << endl;
//		print(tree->left, tree->key, -1);
//		print(tree->right, tree->key, 1);
//	}
//}
//
//template<class T>
//void AVLTree<T>::print()
//{
//	if (root != NULL)
//		print(root, root->key, 0);
//}