#include <iostream>
#include "binaryTreeNode.h"
using namespace std;

int main()
{
	binaryTreeNode<char>* root =  CreateBinTree('#');

	nio(root);
	
	system("pause");
	return 0;
}