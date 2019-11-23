#pragma once
#include <iostream>

using namespace std;

class UFSet
{
private:
	int Num;
		//���鼯Ԫ������
	int* Father;
		//���鼯��Father�����ʾ
public:
	UFSet() { Num = 0; Father = NULL; }
	~UFSet() { if (Father != NULL)delete[]Father; }

	void MS(int x);
			//ΪԪ��x����һ�õ��ڵ���
	void UN(int x, int y);
			//�ϲ�x��y���ڵ�������
	int FD(int x);
			//����Ԫ��x���ڵ����ĸ��ڵ�
	//��������
	//void Create(int n);
	//		//������ʼ���鼯
	//int GetSetCount();
	//		//��ѯ���鼯�еļ��ϸ���
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