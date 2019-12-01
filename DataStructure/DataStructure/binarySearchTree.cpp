#include "binarySearchTree.h"
#include "AVLTree.h"

using namespace std;

int main()
{
	//����������
	/*BinarySearchTreeNode<int>* bst = new BinarySearchTreeNode<int>(1);
	int number;
	for (int i = 0; i < 5; i++)
	{
		cout << "������������: ";
		cin >> number;
		Insert(bst, number);
	}
	inOrder(bst);*/

	//AVL��
	int number;
	AVLTree<int> avlTree;
	for (int i = 0; i < 5; i++)
	{
		cout << "Please input a number: ";
		cin >> number;
		avlTree.insert(number);
	}
	avlTree.inOrder();

	cout << "Now you can delete a number:";
	cin >> number;
	avlTree.remove(number);
	avlTree.inOrder();

	system("pause");
	return 0;
}