#pragma once
#include "stack.h"
#include "myException.h"
#include <iostream>

/*
	10.26	搞了一遍
*/

using namespace std;

template<class T>
class arrayStack : public stack<T>
{
public:
	arrayStack(int initialCapacity = 10);
	~arrayStack() { delete[] stack; }

	bool empty() const { return stackTop == -1; }
	int size() const { return stackTop + 1; }
	void pop()
	{
		if (stackTop == -1)
			throw stackEmpty();
		stack[stackTop--].~T();
	}
	T& top()
	{
		if (stackTop == -1)
			throw stackEmpty();
		return stack[stackTop];
	}
	void push(const T& theElement);
private:
	int stackTop;
	int arrayLength;
	T* stack;
};

//构造函数
template<class T>
arrayStack<T>::arrayStack(int initialCapacity)
{
	if (initialCapacity < 1)
	{
		cout << "Bad initialCapacity." << endl;
		return;
	}
	arrayLength = initialCapacity;
	stack = new T[arrayLength];
	stackTop = -1;
}

//将元素theElement压入栈		2
template<class T>
void arrayStack<T>::push(const T& theElement)
{
	if (stackTop == arrayLength - 1)
	{
		cout << "栈已满" << endl;
		return;
	}
	stack[++stackTop] = theElement;
}

//括号匹配	3
bool matchBrackets(string expr)
{
	arrayStack<char> stack;
	for (int i = 0; i < expr.size(); i++)
	{
		if (expr[i] == '{' || expr[i] == '[' || expr[i] == '(')
		{
			stack.push(expr[i]);
		}
		else if (expr[i] == '}' || expr[i] == ']' || expr[i] == ')')
		{
			if (stack.empty())
			{
				cout << "Unmatched closing bracket" << endl;
				return false;
			}
			char open_bracket = stack.top();
			stack.pop();
			if (!((open_bracket == '(' && expr[i] == ')')
				|| (open_bracket == '[' && expr[i] == ']')
				|| (open_bracket == '{' && expr[i] == '}')))
			{
				cout << "Unmatched closing bracket" << endl;
				return false;
			}
		}
	}
	if (!stack.empty())
	{
		cout << "Unmatched bracket" << endl;
		return false;
	}
	else
	{
		cout << "Matched bracket" << endl;
		return true;
	}
}


