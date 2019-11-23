#pragma once
#include <iostream>

using namespace std;

class UnionFindSet
{
private:
	int Num;
		//并查集元素总数
	int* Father;
		//并查集的Father数组表示
public:
	UnionFindSet() { Num = 0; Father = NULL; }
	~UnionFindSet() { if (Father != NULL)delete[]Father; }

	void Make_Set(int x);
		//为元素x生成一棵单节点树，支持按秩合并
	void Union(int x, int y);
		//合并x和y所在的两棵树，使用按秩合并策略
	int Find(int x);
		//查找元素x所在树的根节点，使用路径压缩策略

	//其他操作
	void Create(int n);
	int GetSetCount();
};

void UnionFindSet::Make_Set(int x)
{
	Father[x] = 0;
}

int UnionFindSet::Find(int x)
{
	if (Father[x] <= 0)
		return x;
	return Father[x] = Find(Father[x]);
}

void UnionFindSet::Union(int x, int y)
{
	int fx = Find(x), fy = Find(y);
	if (fx == fy)
		return;
	if (Father[fx] < Father[fy])
		Father[fy] = fx;
	else
	{
		if (Father[fx] == Father[fy])
			Father[fy]--;
		Father[fx] = fy;
	}
}
