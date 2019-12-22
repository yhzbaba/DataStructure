#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

using namespace std;

enum COLOR { RED, BLACK };

template<class KEY,class U>
class RB_Node
{
public:
	COLOR RB_COLOR;
	RB_Node* right;
	RB_Node* left;
	RB_Node* parent;
	KEY key;
	U data;
	RB_Node()
	{
		RB_COLOR = BLACK;
		right = left = parent = NULL;
	}
};

template<class KEY,class U>
class RB_Tree
{
public:
	RB_Tree()
	{
		this->m_nullNode = new RB_Node<KEY,U>();
		this->m_root = m_nullNode;
		this->m_nullNode->right = this->m_nullNode->left = this->m_nullNode->parent = this->m_root;
		this->m_nullNode->RB_COLOR = BLACK;
	}

	/*Judge if the RBTree is empty.*/
	bool Empty();
	/*Search the node whose key is 'key'.*/
	RB_Node* find(KEY key);
	/*Insert the node*/
	bool Insert(KEY key, U data);
	/*Fix the character of the red-black tree.*/
	void InsertFixUp(RB_Node<KEY, U>* node);
private:
	RB_Node* m_nullNode;
	RB_Node* m_root;
};

template<class KEY, class U>
bool RB_Tree<KEY, U>::Empty()
{
	if (this->m_root == this->m_nullNode)
		return true;
	else
		return false;
}

template<class KEY, class U>
RB_Node<KEY,U>* RB_Tree<KEY, U>::find(KEY key)
{
	RB_Node<KEY, U>* index = m_root;
	while (index != m_nullNode)
	{
		if (key < index->key)
			index = index->left;
		else if (key > index->right)
			index = index->right;
		else
			break;	// reveal that find the node
	}
	return index;
}

template<class KEY, class U>
bool RB_Tree<KEY, U>::Insert(KEY key, U data)
{
	RB_Node<KEY, U>* insert_point = m_nullNode;
	RB_Node<KEY, U>* index = m_root;
	while (index != m_nullNode)
	{
		insert_point = index;
		if (key < index->key)
			index = index->left;
		else if (key > index->key)
			index = index->right;
		else
			return false;
	}
	RB_Node<KEY, U>* insert_node = new RB_Node<KEY, U>();
	insert_node->key = key;
	insert_node->data = data;
	insert_node->RB_COLOR = RED;
	insert_node->right = insert_node->left = m_nullNode;
	// if the tree to insert is an empty tree
	if (insert_point == m_nullNode)
	{
		m_root = insert_node;
		m_root->parent = m_nullNode;
		m_nullNode->left = m_nullNode->right = m_nullNode->parent = m_root;
	}
	else
	{
		if (key < insert_node->key)
		{
			insert_point->left = insert_node;
		}
		else
		{
			insert_point->right = insert_node;
		}
	}
	// use InsertFixUp to fix the character of the red-black tree.

}

template<class KEY, class U>
void RB_Tree<KEY, U>::InsertFixUp(RB_Node<KEY, U>* node)
{
	while (node->parent->RB_COLOR == RED)
	{
		if (node->parent == node->parent->parent->left)
		{
			RB_Node<KEY, U>* uncle = node->parent->parent->right;
			// situation1: the color of uncle is red
			if (uncle->RB_COLOR == RED)
			{
				
			}
		}
	}
}
