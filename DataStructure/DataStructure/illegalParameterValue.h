#pragma once
#include <string>
#include <iostream>
using std::cout;
using std::endl;
using std::string;

class illegalParameterValue
{
private:
	string message;
public:
	illegalParameterValue() :message("Illegal parameter value") {}
	illegalParameterValue(char* theMessage)
	{
		message = theMessage;
	}
	void outputMessage()
	{
		cout << message << endl;
	}
};
