#pragma once

template<class T>
class stack
{
public:
	virtual ~stack() {}
	virtual bool empty() const = 0;
					//����true,���ҽ���ջΪ��
	virtual int size() const = 0;
					//����ջ��Ԫ�ظ���
	virtual T& top() = 0;
					//����ջ��Ԫ�ص�����
	virtual void pop() = 0;
					//ɾ��ջ��Ԫ��
	virtual void push(const T& theElement) = 0;
					//��Ԫ��theElementѹ��ջ��
};