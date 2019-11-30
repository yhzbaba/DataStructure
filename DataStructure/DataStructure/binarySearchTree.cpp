#include "binarySearchTree.h"

using namespace std;

int main()
{
	BinarySearchTreeNode<int>* bst = new BinarySearchTreeNode<int>(1);
	int number;
	for (int i = 0; i < 5; i++)
	{
		cout << "请输入插入的数: ";
		cin >> number;
		Insert(bst, number);
	}
	inOrder(bst);

	system("pause");
	return 0;
}