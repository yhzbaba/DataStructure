#pragma once
#include <iostream>
#include <string>
#include <vector>

using namespace std;

//主串s中找t
int Index(string s, string t)
{
	int lens = s.length();
	int lent = t.length();
	int i = 0;
	int j = 0;
	while (i < lens && j < lent)
	{
		if (t[j] == s[i])
		{
			++i;
			++j;
		}
		else
		{
			i = i - j + 1;
			j = 0;
		}
	}
	if (j == lent)
		return i - lent;
	else
	{
		return -1;
	}
}

//Fail
vector<int> Fail(string pattern)
{
	vector<int> result;
	if (pattern.size() == 0)
		return result;
	result.push_back(-1);
	int i = 0;
	int j = 1;
	for (j = 1; j < pattern.size(); j++)
	{
		i = result[j - 1];
		while (pattern[j] != pattern[i + 1] && i >= 0)
		{
			i = result[i];
		}
		if (pattern[i] == pattern[i + 1])
			result[j] = i + 1;
		else
			result[j] = -1;
	}
}

//KMP
int kmp(string s, string p)
{
	vector<int> result = Fail(s);
	int i = 0;				//模式串初始位置
	int j = 0;				//目标串初始位置
	int m = p.size();		//模式串长度
	int n = s.size();		//目标串长度

	while (i < m && j < n)
	{
		if (s[i] == p[i])
		{
			i++;
			j++;
		}
		else
		{
			if (i == 0)
				j++;
			else
				i = result[i - 1] + 1;
		}
	}
	if (i < m)
	{
		return -1;
	}
	return j - m;
}
