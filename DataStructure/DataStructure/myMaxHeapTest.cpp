//#include "maxHeap.h"
//#include <cstdlib>
//#include <ctime>
//#include <math.h>
//#include <fstream>
//
//using namespace std;
//
//int main()
//{
//	srand((int)time(0));
//	int sortNumber;
//	cout << "请输入排序元素的个数" << endl;
//	cin >> sortNumber;
//	int* a = new int[sortNumber + 1];
//	for (int i = 0; i < 10; i++)
//	{
//		maxHeap<int> heap(sortNumber);
//		for (int j = 0; j < sortNumber; j++)
//		{
//			int element = rand() % sortNumber;
//			a[j] = element;
//		}
//		heapSort(a, sortNumber);
//	}
//	ofstream outFileResult;
//	outFileResult.open("C:\\Users\\Administrator\\Desktop\\1203Test\\1203Result.txt", ios::app);
//	for (int k = 1; k < sortNumber; k++)
//	{
//		outFileResult << a[k] << " ";
//	}
//	int sum = 0;
//	for (int j = 0; j < 10; j++)
//	{
//		sum += list.top();
//		list.pop();
//	}
//	int average = sum / 10;
//	ofstream outFile;
//	outFile.open("C:\\Users\\Administrator\\Desktop\\1203Test\\1203.txt", ios::app);
//	outFile << "平均比较次数为:" << average << "\n";
//	outFile.close();
//	delete[] a;
//	return 0;
//}
