#pragma once
#include "binaryTreeNode.h"
#include "arrayStack.h"
using namespace std;
class ExprTree
{
private:
	binaryTreeNode<string>* tree;
public:
	binaryTreeNode<string>* CreateExprTree();
	void GetValue(binaryTreeNode<string>* t, double& value);
	binaryTreeNode<string>* GetTree() { return tree; }
	void SetTree(binaryTreeNode<string>* t) { tree = t; }
};

//		2
binaryTreeNode<string>* ExprTree::CreateExprTree()
{
	tree = new binaryTreeNode<string>();
	arrayStack<binaryTreeNode<string>*> aStack;
	string elem;
	cin >> elem;
	binaryTreeNode<string>* lpr, * rpr, * p;
	while (elem != "#")
	{
		if (elem == "+" || elem == "-" || elem == "*" || elem == "/")
		{
			rpr = aStack.top();
			aStack.pop();
			lpr = aStack.top();
			aStack.pop();
			p = new binaryTreeNode<string>(elem);
			p->leftChild = lpr;
			p->rightChild = rpr;
			aStack.push(p);
		}
		else
		{
			p = new binaryTreeNode<string>(elem);
			p->leftChild = NULL;
			p->rightChild = NULL;
			aStack.push(p);
		}
		cin >> elem;
	}
	binaryTreeNode<string>* root = aStack.top();
	aStack.pop();
	tree = root;
}


//???		2
void ExprTree::GetValue(binaryTreeNode<string>* t, double& value)
{
	if (t == NULL)
		return;
	arrayStack<double> caculator;
	arrayStack<AssBinTreeNode<string>*> aStack;
	AssBinTreeNode<string>* ass = new AssBinTreeNode<string>(), * lass, * rass;
	ass->SetPtr(t);
	ass->SetFlag(0);
	aStack.push(ass);

	while (!aStack.empty())
	{
		AssBinTreeNode<string>* result = aStack.top();
		aStack.pop();
		if (result->GetFlag() == 0)
		{
			result->SetFlag(1);
			aStack.push(result);
			if (result->GetPtr()->leftChild != NULL)
			{
				lass->SetFlag(0);
				lass->SetPtr(result->GetPtr()->leftChild);
				aStack.push(lass);
			}
		}
		if (result->GetFlag() == 1)
		{
			result->SetFlag(2);
			aStack.push(result);
			if (result->GetPtr()->rightChild != NULL)
			{
				rass->SetFlag(0);
				rass->SetPtr(result->GetPtr()->rightChild);
				aStack.push(rass);
			}
		}
		if (result->GetFlag() == 2)
		{
			if (result->GetPtr()->leftChild == NULL && result->GetPtr()->rightChild == NULL)
			{
				double a = atof(result->GetPtr()->element.c_str());
				caculator.push(a);
			}
			else
			{
				double operand2 = caculator.top();
				caculator.pop();
				double operand1 = caculator.top();
				caculator.pop();
				string op = result->GetPtr()->element;
				double calResult;
				if (op == "+")
					calResult = operand1 + operand2;
				if (op == "-")
					calResult = operand1 - operand2;
				if (op == "*")
					calResult = operand1 * operand2;
				if (op == "/")
					calResult = operand1 / operand2;
				caculator.push(calResult);
			}
		}
	}
	value = caculator.top();
	caculator.pop();
}

