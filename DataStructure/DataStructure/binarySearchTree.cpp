//#include "binarySearchTree.h"
//#include "AVLTree.h"
//
//using namespace std;
//
//int main()
//{
//	//����������
//	/*BinarySearchTreeNode<int>* bst = new BinarySearchTreeNode<int>(1);
//	int number;
//	for (int i = 0; i < 5; i++)
//	{
//		cout << "������������: ";
//		cin >> number;
//		Insert(bst, number);
//	}
//	inOrder(bst);*/
//
//	//AVL��
//	int number;
//	AVLTree<int> avlTree;
//	for (int i = 0; i < 100; i++)
//	{
//		cout << "Please input a number: ";
//		cin >> number;
//		AVLTreeNode<int>* getNode = avlTree.search(number);
//		if (getNode == NULL)
//		{
//			//˵��û�����Ԫ��
//			avlTree.insert(number);
//			cout << "�µ������������Ϊ:";
//			avlTree.inOrder();
//			cout << endl;
//		}
//		else
//		{
//			//˵�������Ԫ��
//			int level = getLevel(getNode, avlTree.getRoot());
//			cout << "����ڵ�����ˣ����ڲ���Ϊ��" << level << endl;
//		}
//	}
//	avlTree.inOrder();
//
//	system("pause");
//	return 0;
//}