#pragma once
#include <iostream>
#include <string>

using namespace std;

/*长度为3的字符串转换为一个长整型数*/
long threeToLong(string s)
{
	long answer = s.at(0);

	/*左移8位，插入下一个字符*/
	answer = (answer << 8) + s.at(1);

	answer = (answer << 8) + s.at(2);
}
