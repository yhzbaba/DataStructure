#pragma once
#include <iostream>

using namespace std;

class UFSet
{
private:
	int Num;
		//并查集元素总数
	int* Father;
		//并查集的Father数组表示
public:
	UFSet() { Num = 0; Father = NULL; }
	~UFSet() { if (Father != NULL)delete[]Father; }

	void MS(int x);
			//为元素x生成一棵单节点树
	void UN(int x, int y);
			//合并x和y所在的两棵树
	int FD(int x);
			//查找元素x所在的树的根节点
	//其他操作
	//void Create(int n);
	//		//创建初始并查集
	//int GetSetCount();
	//		//查询并查集中的集合个数
};

void UFSet::MS(int x)
{
	Father[x] = x;
}

int UFSet::FD(int x)
{
	if (Father[x] == x)
		return x;
	return FD(Father[x]);
}

void UFSet::UN(int x, int y)
{
	Father[FD(y)] = FD(x);
}