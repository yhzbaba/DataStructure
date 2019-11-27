#pragma once
#include <iostream>
#include <string>

using std::string;


_NODISCARD int stringToInt(string s)
{
	/*��sת��Ϊһ���Ǹ�����������ת������s�������ַ�*/
	int length = (int)s.length();
	int answer = 0;
	if (length % 2 == 1)
	{
		/*����Ϊ����*/
		answer = s.at(length - 1);
		length--;
	}

	for (int i = 0; i < length; i += 2)
	{
		answer += s.at(i);
		answer += ((int)s.at(i + 1)) << 8;
	}

	return (answer < 0) ? -answer : answer;
}

