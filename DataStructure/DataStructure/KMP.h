#pragma once

#include <iostream>
#include <vector>

using namespace std;

void get_next(const char* temp, int next[])
{
	// get the array of next
	int len_temp = strlen(temp);
	next[1] = 0;
	int j = 1;
	int k = -1;	// k is the flag of the array
	while (j < len_temp)
	{
		if (k == -1 || temp[j] == temp[k])
		{
			next[++j] = ++k;
		}
		else
		{
			k = next[k];
		}
	}
}

vector<int> KMP(const char* str, const char* temp)
{
	int __next[100] = { -1 };
	get_next(temp, __next);
	int len_str = strlen(str);
	int len_temp = strlen(temp);
	vector<int> result;
	int i = 0, j = 0;
	while (i < len_str)
	{
		while (j < len_temp && i < len_str)
		{
			if (str[i] == temp[j])
			{
				i++;
				j++;
			}
			else
			{
				if (j == 0)
					i++;	// Fail happens at the first pos
				else
					j = __next[j];
			}
		}
		if (j == len_temp)
		{
			result.push_back(i - j);
			j = 0;
		}
	}
	return result;
}
