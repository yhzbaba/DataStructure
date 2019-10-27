#pragma once
#include <iostream>
using namespace std;

template<class T>
class linearList
{
public:
	virtual ~linearList() {};
	virtual bool empty() const = 0;
				//����true,���ҽ������Ա�Ϊ��
	virtual int size() const = 0;
				//�������Ա�Ԫ�صĸ���
	virtual T& get(int theIndex) const = 0;
				//��������ΪtheIndex��Ԫ��
	virtual void erase(int theIndex) = 0;
				//ɾ������ΪtheIndex��Ԫ��
	virtual void insert(int theIndex, const T& theElement) = 0;
				//��theElement�������Ա�������ΪtheIndex��λ����
	virtual void output(ostream& out) const = 0;
				//�����Ա���������out
};