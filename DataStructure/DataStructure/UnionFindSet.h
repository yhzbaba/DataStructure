#pragma once
#include <iostream>

using namespace std;

class UnionFindSet
{
private:
	int Num;
		//���鼯Ԫ������
	int* Father;
		//���鼯��Father�����ʾ
public:
	UnionFindSet() { Num = 0; Father = NULL; }
	~UnionFindSet() { if (Father != NULL)delete[]Father; }

	void Make_Set(int x);
		//ΪԪ��x����һ�õ��ڵ�����֧�ְ��Ⱥϲ�
	void Union(int x, int y);
		//�ϲ�x��y���ڵ���������ʹ�ð��Ⱥϲ�����
	int Find(int x);
		//����Ԫ��x�������ĸ��ڵ㣬ʹ��·��ѹ������

	//��������
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
