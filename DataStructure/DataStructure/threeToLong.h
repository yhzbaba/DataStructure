#pragma once
#include <iostream>
#include <string>

using namespace std;

/*����Ϊ3���ַ���ת��Ϊһ����������*/
long threeToLong(string s)
{
	long answer = s.at(0);

	/*����8λ��������һ���ַ�*/
	answer = (answer << 8) + s.at(1);

	answer = (answer << 8) + s.at(2);
}
