#pragma once
#include "arrayStack.h"
#include <string>
#include <iostream>

using namespace std;

//定义优先级
string priority = "#(+-*/)";
/*
	# --0
	( --1
	+ --2
	- --2
	* --4
	/ --4
	) --6
*/

int locate(char c, string str)
{
	int locate = str.find(c);
	if (locate == 2 || locate == 3)
	{
		return 2;
	}
	else
	{
		if (locate == 4 || locate == 5)
		{
			return 4;
		}
		else
		{
			return locate;
		}
	}
}

string MidToBack(string str)
{
	string temp = "";
	arrayStack<char> s;
	s.push('#');

	for (int i = 0; i < str.length(); i++)
	{
		switch (str[i])
		{
		case '(':
			s.push('(');
			break;
		case ')':
			while (!s.empty() && s.top() != '(')
			{
				temp = temp + s.top();
				s.pop();
			}
			//再将(出栈
			s.pop();
			break;
		default:
			if (isalpha(str[i]))
			{
				temp = temp + str[i];
			}
			else
			{
				if ((s.top() == '(') || (s.top() != '(' &&
					locate(str[i], priority) > locate(s.top(), priority)))
				{
					s.push(str[i]);
				}
				else
				{
					while (locate(str[i], priority) <= locate(s.top(), priority))
					{
						temp = temp + s.top();
						s.pop();
					}
					s.push(str[i]);
				}
			}
			break;
		}
		while (!s.empty())
		{
			temp = temp + s.top();
			s.pop();
		}
		return temp;
	}
}
