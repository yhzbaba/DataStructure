//#include "binarySearchTree.h"
//#include "AVLTree.h"
//
//using namespace std;
//
//int main()
//{
//	//二叉搜索树
//	/*BinarySearchTreeNode<int>* bst = new BinarySearchTreeNode<int>(1);
//	int number;
//	for (int i = 0; i < 5; i++)
//	{
//		cout << "请输入插入的数: ";
//		cin >> number;
//		Insert(bst, number);
//	}
//	inOrder(bst);*/
//
//	//AVL树
//	int number;
//	AVLTree<int> avlTree;
//	for (int i = 0; i < 100; i++)
//	{
//		cout << "Please input a number: ";
//		cin >> number;
//		AVLTreeNode<int>* getNode = avlTree.search(number);
//		if (getNode == NULL)
//		{
//			//说明没有这个元素
//			avlTree.insert(number);
//			cout << "新的中序遍历序列为:";
//			avlTree.inOrder();
//			cout << endl;
//		}
//		else
//		{
//			//说明有这个元素
//			int level = getLevel(getNode, avlTree.getRoot());
//			cout << "这个节点存在了，所在层数为：" << level << endl;
//		}
//	}
//	avlTree.inOrder();
//
//	system("pause");
//	return 0;
//}