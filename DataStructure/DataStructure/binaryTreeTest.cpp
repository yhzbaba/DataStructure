#include <iostream>
#include "binaryTreeNode.h"
using namespace std;

int main()
{
	binaryTreeNode<int>* root = CreateBinTree(0);

	int path[100];
	int pathLen = 0;
	PrintPathsRecur(root, path, pathLen);

	system("pause");
	return 0;
}