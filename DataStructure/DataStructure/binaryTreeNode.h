#pragma once
#include <iostream>
#include <vector>
#include "arrayQueue.h"
#include "arrayStack.h"
using namespace std;
/*
	10.26	全部重写了一遍
*/

template<class T>
struct binaryTreeNode
{
	T element;
	binaryTreeNode<T>* leftChild;
	binaryTreeNode<T>* rightChild;

	binaryTreeNode() { leftChild = rightChild = NULL; }
	binaryTreeNode(const T& theElement)
	{
		element(theElement);
		leftChild = rightChild = NULL;
	}
	binaryTreeNode(const T& theElement, binaryTreeNode<T>* theLeftChild, binaryTreeNode<T>* theRightChild)
	{
		element = theElement;
		leftChild = theLeftChild;
		rightChild = theRightChild;
	}
};

//visit函数
template<class T>
void visit(binaryTreeNode<T>* x)
{
	cout << x->element << ' ';
}

//前序遍历
template<class T>
void preOrder(binaryTreeNode<T>* t)
{
	if (t != NULL)
	{
		visit(t);
		preOrder(t->leftChild);
		preOrder(t->rightChild);
	}
}

//中序遍历
template<class T>
void inOrder(binaryTreeNode<T>* t)
{
	if (t != NULL)
	{
		inOrder(t->leftChild);
		visit(t);
		inOrder(t->rightChild);
	}
}

//后序遍历
template<class T>
void postOrder(binaryTreeNode<T>* t)
{
	if (t != NULL)
	{
		postOrder(t->leftChild);
		postOrder(t->rightChild);
		visit(t);
	}
}

//后缀转中缀
template<class T>
void infix(binaryTreeNode<T>* t)
{
	if (t != NULL)
	{
		cout << '(';
		infix(t->leftChild);
		cout << t->element;
		infix(t->rightChild);
		cout << ')';
	}
}

//层次遍历
template<class T>
void levelOrder(binaryTreeNode<T>* t)
{
	arrayQueue<binaryTreeNode<T>*> q;
	while (t != NULL)
	{
		visit(t);

		if (t->leftChild != NULL)
			q.push(t->leftChild);
		if (t->rightChild != NULL)
			q.push(t->rightChild);

		try
		{
			t = q.front();
		}
		catch (queueEmpty)
		{
			return;
		}
		q.pop();
	}
}


//NIO		5
template<class T>
void nio(binaryTreeNode<T>* t)
{
	if (t == NULL)
		return;

	arrayStack<binaryTreeNode<T>*> aStack;
	while (t != NULL || !aStack.empty())
	{
		while (t != NULL)
		{
			aStack.push(t);
			t = t->leftChild;
		}
		if (aStack.empty())
		{
			return;
		}
		t = aStack.top();
		aStack.pop();
		cout << t->element << endl;
		t = t->rightChild;
	}
}

//NPO
template<class T>
class AssBinTreeNode
{
private:
	binaryTreeNode<T>* ptr;
	int flag;
public:
	AssBinTreeNode(binaryTreeNode<T>* p = NULL, int i = 0) :ptr(p), flag(i) {}
	int GetFlag() { return flag; }
	void SetFlag(int i) { flag = i; }
	binaryTreeNode<T>* GetPtr() { return ptr; }
	void SetPtr(binaryTreeNode<T>* p) { ptr = p; }
};

//			4
template<class T>
void npo(binaryTreeNode<T>* t)
{
	if (t == NULL)
		return;

	arrayStack<AssBinTreeNode<T>*> aStack;
	AssBinTreeNode<T>* ass;
	AssBinTreeNode<T>* lass;
	AssBinTreeNode<T>* rass;
	ass = new AssBinTreeNode<T>();
	ass->SetFlag(0);
	ass->SetPtr(t);
	aStack.push(ass);
	int i = 0;
	while (!aStack.empty())
	{
		ass = aStack.top();
		t = ass->GetPtr();
		i = ass->GetFlag();
		if (i == 0)
		{
			ass->SetFlag(1);
			aStack.push(ass);
			if (t->leftChild != NULL)
			{
				lass = new AssBinTreeNode<T>(t->leftChild, 0);
				lass->SetFlag(0);
				aStack.push(lass);
			}
		}
		if (i == 1)
		{
			ass->SetFlag(2);
			aStack.push(ass);
			if (t->rightChild != NULL)
			{
				rass = new AssBinTreeNode<T>(t->rightChild, 0);
				rass->SetFlag(0);
				aStack.push(rass);
			}
		}
		if (i == 2)
			cout << t->element << endl;
	}
}


//CBT			2
template<class T>
binaryTreeNode<T>* CreateBinTree(T tostop)
{
	binaryTreeNode<T>* t, * t1, * t2;
	T item;
	cin >> item;
	if (item == tostop)
	{
		t = NULL;
		return t;
	}
	else
	{
		if (!(t = new binaryTreeNode<T>(item, NULL, NULL)))
			return NULL;
		t1 = CreateBinTree(tostop);
		t->leftChild = t1;
		t2 = CreateBinTree(tostop);
		t->rightChild = t2;
		return t;
	}
}

//CopyTree		2
template<class T>
binaryTreeNode<T>* CopyTree(binaryTreeNode<T>* t)
{
	if (t == NULL)
		return NULL;
	binaryTreeNode<T>* newlptr, * newrptr;
	if (t->leftChild != NULL)
		newlptr = CopyTree(t->leftChild);
	else
		newlptr = NULL;
	if (t->rightChild != NULL)
		newrptr = CopyTree(t->rightChild);
	else
		newrptr = NULL;
	binaryTreeNode<T>* newNode = new binaryTreeNode<T>(t->element, newlptr, newrptr);
	return newNode;
}

//Father	在t中寻找p的父亲		2
template<class T>
binaryTreeNode<T>* Father(binaryTreeNode<T>* t, binaryTreeNode<T>* p)
{
	binaryTreeNode<T>* q;
	if (t == NULL || p == NULL)
		return NULL;
	if (t->leftChild == p || t->rightChild == p)
		return t;
	binaryTreeNode<T>* qL = Father(t->leftChild, p);
	if (qL != NULL)
	{
		q = qL;
		return q;
	}
	else
	{
		return Father(t->rightChild, p);
	}
}

//Find			2
template<class T>
binaryTreeNode<T>* Find(binaryTreeNode<T>* t, const T& item)
{
	binaryTreeNode<T>* p, * q;
	if (t == NULL)
		return NULL;
	if (t->element == item)
		return t;
	p = Find(t->leftChild, item);
	if (p != NULL)
	{
		return p;
	}
	else
	{
		q = Find(t->rightChild, item);
		return q;
	}
}

//Del
template<class T>
void Del(binaryTreeNode<T>* t)
{
	if (t != NULL)
	{
		Del(t->leftChild);
		Del(t->rightChild);
		delete t;
	}
}

//结点t的左侧插入data域为item的结点
template<class T>
void InsertLeft(binaryTreeNode<T>* t, T item)
{
	if (t == NULL)
		return;
	binaryTreeNode<T>* p = new binaryTreeNode<T>(item);
	p->leftChild = t->leftChild;
	t->leftChild = p;
}

//删除结点
template<class T>
void DelSubtree(binaryTreeNode<T>* root,binaryTreeNode<T>* t)
{
	if (t == NULL)
		return;
	if (t == root)
	{
		delete t;
		root = NULL;
		return;
	}
	binaryTreeNode<T>* p, * q;
	p = t;
	q = Father(root, p);
	if (q)
	{
		if (q->leftChild == p)
			q->leftChild = NULL;
		if (q->rightChild == p)
			q->rightChild = NULL;
	}
	delete p;
}

//统计树的结点数		2
template<class T>
int getNodeCount(binaryTreeNode<T>* t)
{
	if (t == NULL)
		return 0;
	int lCount = getNodeCount(t->leftChild);
	int rCount = getNodeCount(t->rightChild);
	int ret = lCount + rCount + 1;
	return ret;
}

//计算树的宽度		2
template<class T>
int widthOfBinaryTree(binaryTreeNode<T>* pNode)
{
	if (pNode == NULL)
		return 0;
	arrayQueue<T> aQueue;
	int maxWidth = 1;
	aQueue.push(pNode);
	while (true)
	{
		int length = aQueue.size();
		if (length == 0)
			break;
		while (length > 0)
		{
			binaryTreeNode<T>* temp = aQueue.front();
			aQueue.pop();
			length--;
			if (temp->leftChild != NULL)
				aQueue.push(temp->leftChild);
			if (temp->rightChild != NULL)
				aQueue.push(temp->rightChild);
		}
		//更新maxWidth的值
		maxWidth = maxWidth > aQueue.size() ? maxWidth : aQueue.size();
	}
	return maxWidth;
}

template<class T>
vector<int> allWidthOfBinaryTree(binaryTreeNode<T>* pNode)
{
	vector<int> ret;
	arrayQueue<binaryTreeNode<T>*> aQueue;
	aQueue.push(pNode);
	while (true)
	{
		int length = aQueue.size();
		if (length == 0)
			break;
		ret.push_back(length);
		while (length > 0)
		{
			binaryTreeNode<T>* temp = aQueue.front();
			if (temp->leftChild != NULL)
				aQueue.push(temp->leftChild);
			if (temp->rightChild != NULL)
				aQueue.push(temp->rightChild);
			length--;
		}
	}
	return ret;
}

/*Find the max element in a binary tree.*/
template<class T>
T FindMax(binaryTreeNode<T>* root)
{
	T root_val, left, right, max = (T)INT_MIN;
	if (root != NULL)
	{
		root_val = root->element;
		left = FindMax(root->leftChild);
		right = FindMax(root->rightChild);
		if (left > right)
			max = left;
		else
			max = right;
		if (root_val > max)
		{
			max = root_val;
		}
	}
	return max;
}

/*Find the min element in a binary tree.*/
template<class T>
T FindMaxUsingLevelOrder(binaryTreeNode<T>* root)
{
	//运用二叉树的层次遍历，只需要在删除元素时观察该元素
	binaryTreeNode<T>* temp;
	int max = INT_MIN;
	arrayQueue<binaryTreeNode<T>*> Q;
	Q.push(root);
	while (!Q.empty())
	{
		temp = Q.front();
		Q.pop();
		//树的最大元素
		if (max < temp->element)
			max = temp->element;
		if (temp->leftChild)
			Q.push(root->leftChild);
		if (temp->rightChild)
			Q.push(root->rightChild);
	}
	Q.~arrayQueue();
	return max;
}

/*Insert an element into a binary tree*/
template<class T>
void InsertInBinaryTree(binaryTreeNode<T>* root, T data)
{
	arrayQueue<T> Q;
	binaryTreeNode<T>* temp, * newNode;
	newNode = new binaryTreeNode<T>();
	newNode->leftChild = newNode->rightChild = NULL;
	if (!newNode){
		cout << "Memory Error." << endl;
		return;
	}
	if (!root) {
		root = newNode;
		return;
	}
	Q.push(root);
	while (!Q.empty()){
		temp = Q.front();
		if (temp->leftChild)
			Q.push(temp->leftChild);
		else {
			temp->leftChild = newNode;
			Q.~arrayQueue();
			return;
		}
		if (temp->rightChild)
			Q.push(temp->rightChild);
		else {
			temp->rightChild = newNode;
			Q.~arrayQueue();
			return;
		}
	}
	Q.~arrayQueue();
}

/*Count the nodes in the binary tree*/
template<class T>
int SizeOfBinaryTree(binaryTreeNode<T>* root) {
	if (root == NULL)
		return 0;
	else
		return SizeOfBinaryTree(root->leftChild)
		+ SizeOfBinaryTree(root->rightChild) + 1;
}

/*Count the nodes without incursion*/
template<class T>
int SizeofBTUsingLevelOrder(binaryTreeNode<T>* root)
{
	binaryTreeNode<T>* temp;
	arrayQueue<T> Q;
	int count = 0;
	if (!root)
		return 0;
	Q.push(root);
	while (!Q.empty())
	{
		temp = Q.front();
		Q.pop();
		count++;
		if (temp->leftChild)
			Q.push(temp->leftChild);
		if (temp->rightChild)
			Q.push(temp->rightChild);
	}
	Q.~arrayQueue();
	return count;
}

/*Find the deepest node int the binary tree*/
template<class T>
binaryTreeNode<T>* DeepestNodeinBinaryTree(binaryTreeNode<T>* root)
{
	binaryTreeNode<T>* temp;
	arrayQueue<T> Q;
	if (!root)
		return NULL;
	Q.push(root);
	while (!Q.empty())
	{
		temp = Q.front();
		Q.pop();
		if (temp->leftChild)
			Q.push(temp->leftChild);
		if (temp->rightChild)
			Q.push(temp->rightChild);
	}
	Q.~arrayQueue();
	return temp;
}

//给出一个算法，求二叉树的高度
template<class T>
int HeightOfBinaryTree(binaryTreeNode<T>* root)
{
	int leftHeight, rightHeight;
	if (root == NULL)
		return 0;
	else
	{
		leftHeight = HeightOfBinaryTree(root->leftChild);
		rightHeight = HeightOfBinaryTree(root->rightChild);

		if (leftHeight > rightHeight)
			return leftHeight + 1;
		else
			return rightHeight + 1;
	}
}

//不用递归的方式解决上一个问题
template<class T>
int FindHeightofBinaryTree(binaryTreeNode<T>* root)
{
	int level = 0;
	arrayQueue<binaryTreeNode<T>*> Q;
	if (!root)
	{
		return 0;
	}
	Q.push(root);
	//第一层结束
	Q.push(NULL);
	while (!Q.empty())
	{
		root = Q.front();
		Q.pop();
		//当前层结束
		if (root == NULL)
		{
			//压入下一层的结束标记
			if (!Q.empty())
				Q.push(NULL);
			level++;
		}
		else {
			if (root->leftChild)
				Q.push(root->leftChild);
			if (root->rightChild)
				Q.push(root->rightChild);
		}
	}
	return level;
}

//判断两棵二叉树是否是结构相同的
template<class T>
int AreStructurullySameTrees(binaryTreeNode<T>* root1, binaryTreeNode<T>* root2)
{
	if (root1 == NULL && root2 == NULL)
		return 1;
	else if (root1 == NULL || root2 == NULL)
		return 0;
	return (root1->element == root2->element && AreStructurullySameTrees(root1->leftChild, root2->rightChild)
		&& AreStructurullySameTrees(root1->rightChild, root2->rightChild));
}

//给出一个算法，求二叉树的直径，两个叶子节点之间的最长路径的节点个数
//我们需要计算所有结点的所有左右子树的高度之和，其中的最大值就是二叉树的直径
//template<class T>
//int DiameterOfTree(binaryTreeNode<T>* root, int* ptr)
//{
//	int left, right;
//	if (!root)
//		return 0;
//	left = DiameterOfTree(root->leftChild, ptr);
//	right = DiameterOfTree(root->rightChild, ptr);
//	if (left + right > * ptr)
//		* ptr = left + right;
//	return max(left, right) + 1;
//}

//给出一个算法，找出二叉树中节点值之和最大的层
template<class T>
int FindLevelWithMaxSum(binaryTreeNode<T>* root)
{
	binaryTreeNode<T>* temp;
	int level = 0, maxLevel = 0;
	arrayQueue<binaryTreeNode<T>*> Q;
	int currentSum = 0, maxSum = 0;
	if (!root)
		return 0;
	Q.push(root);
	//第一层结束
	Q.push(NULL);
	while (!Q.empty())
	{
		temp = Q.front();
		Q.pop();
		//如果当前层遍历完则比较和
		if (temp == NULL)
		{
			if (currentSum > maxSum)
			{
				maxSum = currentSum;
				maxLevel = level;
			}
			currentSum = 0;
			//将下一层结束标记插入队尾
			if (!Q.empty())
			{
				Q.push(NULL);
			}
			level++;
		}
		else
		{
			currentSum += temp->element;
			if (temp->leftChild)
				Q.push(temp->leftChild);
			if (temp->rightChild)
				Q.push(temp->rightChild);
		}
	}
}

void PrintArray(int ints[], int len)
{
	for (int i = 0; i < len; i++)
	{
		printf("%d ", ints[i]);
	}
	cout << endl;
}

//给出算法，输出二叉树中所有根到叶子节点的路径信息
void PrintPathsRecur(binaryTreeNode<int>* root, int path[], int pathLen)
{
	if (root == NULL)
		return;
	//将根节点添加到路径数组中
	path[pathLen] = root->element;
	pathLen++;

	//如果是叶子节点，则打印从根节点到该叶子节点的路径信息
	if (root->leftChild == NULL && root->rightChild == NULL)
		PrintArray(path, pathLen);
	else
	{
		PrintPathsRecur(root->leftChild, path, pathLen);
		PrintPathsRecur(root->rightChild, path, pathLen);
	}
}

//问题21给出一个算法，判断二叉树中是否存在一条路径，节点值和=sum
//在递归判断当前节点的左右孩子之前，从sum减去当前结点的值，到达边界判断sum是否为0
template<class T>
int HasPathSum(binaryTreeNode<T>* root, int sum)
{
	//如果我们访问完树且sum=0,那么我们返回true
	if (root == NULL)
		return sum == 0;
	else {
		//否则判断两棵子树
		int remainingSum = sum - root->element;
		if ((root->leftChild && root->rightChild) || (!root->leftChild && !root->rightChild))
		{
			return (HasPathSum(root->leftChild, remainingSum) ||
				HasPathSum(root->rightChild, remainingSum));
		}
		else if (root->leftChild)
			return HasPathSum(root->leftChild, remainingSum);
		else
			return HasPathSum(root->rightChild, remainingSum);
	}
}

// 非递归计算二叉树中所有节点之和
template<class T>
int SumofBTusingLevelOrder(binaryTreeNode<T>* root)
{
	binaryTreeNode<T>* temp;
	arrayQueue<binaryTreeNode<T>*> Q;
	int sum = 0;
	if (!root)
		return 0;
	Q.push(root);
	while (!Q.empty())
	{
		temp = Q.front();
		Q.pop();
		sum += temp->element;
		if (temp->leftChild)
			Q.push(temp->leftChild);
		if (temp->rightChild)
			Q.push(temp->rightChild);
	}
	Q.~arrayQueue();
	return sum;
}

//求二叉树在镜子中的像
template<class T>
binaryTreeNode<T>* MirrorOfBinaryTree(binaryTreeNode<T>* root)
{
	binaryTreeNode<T>* temp;
	if (root)
	{
		MirrorOfBinaryTree(root->leftChild);
		MirrorOfBinaryTree(root->rightChild);
		temp = root->leftChild;
		root->leftChild = root->rightChild;
		root->rightChild = temp;
	}
	return root;
}

//判断两棵二叉树是否互为镜子中的像
template<class T>
int AreMirrors(binaryTreeNode<T>* root1, binaryTreeNode<T>* root2)
{
	if (root1 == NULL && root2 == NULL)
		return 1;
	if (root1 == NULL || root2 == NULL)
		return 0;
	if (root1->element != root2->element)
		return 0;
	else return AreMirrors(root1->leftChild, root2->rightChild) 
		&& AreMirrors(root1->rightChild, root2->leftChild);
}

// LCA重点问题！！！！
// 给出一个算法，求解二叉树中给定两个节点的最近共同祖先
template<class T>
binaryTreeNode<T>* LCA(binaryTreeNode<T>* root, binaryTreeNode<T>* a, binaryTreeNode<T>* b)
{
	binaryTreeNode<T>* left,* right;
	if (root == NULL)
		return NULL;
	if (root == a || root == b)
	{
		return root;
	}
	left = LCA(root->leftChild, a, b);
	right = LCA(root->rightChild, a, b);
	if (left && right)
		return root;
	else
		return (left ? left : right);
}

//用中序和先序构造一棵二叉树
template<class T>
binaryTreeNode<T>* BuildBinaryTree(int inOrder[], int preOrder[], int inOrderStart, int inOrderEnd)
{
	static int preOrderIndex = 0;
	binaryTreeNode<T>* newNode;
	if (inOrderStart > inOrderEnd)
		return NULL;
	newNode = new binaryTreeNode<T>();
	if (!newNode)
	{
		printf("Memory Error!");
		return NULL;
	}
	//利用preOrderIndex从先序遍历序列中选出当前结点
	newNode->element = preOrder[preOrderIndex];
	preOrderIndex++;
	if (inOrderStart == inOrderEnd)
		return newNode;
	int inOrderIndex = 0;
	//查找该结点在中序遍历序列中的位序
	for (int i = inOrderStart; i <= inOrderEnd; i++)
	{
		if (inOrder[i] == newNode->element)
			inOrderIndex = i;
	}
	//填充左右子树
	newNode->leftChild = BuildBinaryTree(inOrder, preOrder, inOrderStart, inOrderIndex - 1);
	newNode->rightChild = BuildBinaryTree(inOrder, preOrder, inOrderIndex + 1, inOrderEnd);
	return newNode;
}

//打印二叉树中所有指定结点的所有祖先
//DFS怎么做呢???
template<class T>
T PrintAllAncestors(binaryTreeNode<T>* root, binaryTreeNode<T>* node)
{
	if (root == NULL)
		return 0;
	if (root->leftChild == node || root->rightChild == node || PrintAllAncestors(root->leftChild, node)
		|| PrintAllAncestors(root->rightChild, node))
	{
		cout << root->element << " ";
		return 1;
	}
	return 0;
}

//问题30了









//以下是普通树的问题
struct TreeNode
{
	int data;
	struct TreeNode* firstChild;
	struct TreeNode* nextSibling;
};

//给出一个算法，求出树中所有节点的值之和
int FindSum(struct TreeNode* root)
{
	if (!root)
		return 0;
	return root->data + FindSum(root->firstChild) + FindSum(root->nextSibling);
}

//给定一个双亲数组P，其中P[i]表示的是树中第i个结点的双亲，给出算法求高度
int FindDepthInGenericTree(int P[], int n)
{
	int maxDepth = -1, currentDepth = -1, j;
	for (int i = 0; i < n; i++)
	{
		currentDepth = 0;
		j = i;
		while (P[j] != -1)
		{
			currentDepth++; j = P[j];
		}
		if (currentDepth > maxDepth)
			maxDepth = currentDepth;
	}
	return maxDepth;
}



