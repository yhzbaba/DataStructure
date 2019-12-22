#pragma once
#include <iostream>
#include <vector>
#include "arrayQueue.h"
#include "arrayStack.h"
using namespace std;
/*
	10.26	ȫ����д��һ��
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

//visit����
template<class T>
void visit(binaryTreeNode<T>* x)
{
	cout << x->element << ' ';
}

//ǰ�����
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

//�������
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

//�������
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

//��׺ת��׺
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

//��α���
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

//Father	��t��Ѱ��p�ĸ���		2
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

//���t��������data��Ϊitem�Ľ��
template<class T>
void InsertLeft(binaryTreeNode<T>* t, T item)
{
	if (t == NULL)
		return;
	binaryTreeNode<T>* p = new binaryTreeNode<T>(item);
	p->leftChild = t->leftChild;
	t->leftChild = p;
}

//ɾ�����
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

//ͳ�����Ľ����		2
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

//�������Ŀ��		2
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
		//����maxWidth��ֵ
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
	//���ö������Ĳ�α�����ֻ��Ҫ��ɾ��Ԫ��ʱ�۲��Ԫ��
	binaryTreeNode<T>* temp;
	int max = INT_MIN;
	arrayQueue<binaryTreeNode<T>*> Q;
	Q.push(root);
	while (!Q.empty())
	{
		temp = Q.front();
		Q.pop();
		//�������Ԫ��
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

//����һ���㷨����������ĸ߶�
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

//���õݹ�ķ�ʽ�����һ������
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
	//��һ�����
	Q.push(NULL);
	while (!Q.empty())
	{
		root = Q.front();
		Q.pop();
		//��ǰ�����
		if (root == NULL)
		{
			//ѹ����һ��Ľ������
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

//�ж����ö������Ƿ��ǽṹ��ͬ��
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

//����һ���㷨�����������ֱ��������Ҷ�ӽڵ�֮����·���Ľڵ����
//������Ҫ�������н����������������ĸ߶�֮�ͣ����е����ֵ���Ƕ�������ֱ��
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

//����һ���㷨���ҳ��������нڵ�ֵ֮�����Ĳ�
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
	//��һ�����
	Q.push(NULL);
	while (!Q.empty())
	{
		temp = Q.front();
		Q.pop();
		//�����ǰ���������ȽϺ�
		if (temp == NULL)
		{
			if (currentSum > maxSum)
			{
				maxSum = currentSum;
				maxLevel = level;
			}
			currentSum = 0;
			//����һ�������ǲ����β
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

//�����㷨����������������и���Ҷ�ӽڵ��·����Ϣ
void PrintPathsRecur(binaryTreeNode<int>* root, int path[], int pathLen)
{
	if (root == NULL)
		return;
	//�����ڵ���ӵ�·��������
	path[pathLen] = root->element;
	pathLen++;

	//�����Ҷ�ӽڵ㣬���ӡ�Ӹ��ڵ㵽��Ҷ�ӽڵ��·����Ϣ
	if (root->leftChild == NULL && root->rightChild == NULL)
		PrintArray(path, pathLen);
	else
	{
		PrintPathsRecur(root->leftChild, path, pathLen);
		PrintPathsRecur(root->rightChild, path, pathLen);
	}
}

//����21����һ���㷨���ж϶��������Ƿ����һ��·�����ڵ�ֵ��=sum
//�ڵݹ��жϵ�ǰ�ڵ�����Һ���֮ǰ����sum��ȥ��ǰ����ֵ������߽��ж�sum�Ƿ�Ϊ0
template<class T>
int HasPathSum(binaryTreeNode<T>* root, int sum)
{
	//������Ƿ���������sum=0,��ô���Ƿ���true
	if (root == NULL)
		return sum == 0;
	else {
		//�����ж���������
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

// �ǵݹ��������������нڵ�֮��
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

//��������ھ����е���
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

//�ж����ö������Ƿ�Ϊ�����е���
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

// LCA�ص����⣡������
// ����һ���㷨�����������и��������ڵ�������ͬ����
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

//�������������һ�ö�����
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
	//����preOrderIndex���������������ѡ����ǰ���
	newNode->element = preOrder[preOrderIndex];
	preOrderIndex++;
	if (inOrderStart == inOrderEnd)
		return newNode;
	int inOrderIndex = 0;
	//���Ҹý����������������е�λ��
	for (int i = inOrderStart; i <= inOrderEnd; i++)
	{
		if (inOrder[i] == newNode->element)
			inOrderIndex = i;
	}
	//�����������
	newNode->leftChild = BuildBinaryTree(inOrder, preOrder, inOrderStart, inOrderIndex - 1);
	newNode->rightChild = BuildBinaryTree(inOrder, preOrder, inOrderIndex + 1, inOrderEnd);
	return newNode;
}

//��ӡ������������ָ��������������
//DFS��ô����???
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

//����30��









//��������ͨ��������
struct TreeNode
{
	int data;
	struct TreeNode* firstChild;
	struct TreeNode* nextSibling;
};

//����һ���㷨������������нڵ��ֵ֮��
int FindSum(struct TreeNode* root)
{
	if (!root)
		return 0;
	return root->data + FindSum(root->firstChild) + FindSum(root->nextSibling);
}

//����һ��˫������P������P[i]��ʾ�������е�i������˫�ף������㷨��߶�
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



