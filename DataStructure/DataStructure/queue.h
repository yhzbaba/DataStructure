#pragma once

template<class T>
class queue
{
public:
	virtual ~queue() {}
	virtual bool empty() const = 0;
					//����true,���ҽ�������Ϊ��
	virtual int size() const = 0;
					//���ض�����Ԫ�ظ���
	virtual T& front() = 0;
					//����ͷԪ������
	virtual T& back() = 0;
					//����βԪ������
	virtual void pop() = 0;
					//ɾ����Ԫ��
	virtual void push(const T& theElement) = 0;
					//��Ԫ��theElement�����β
};