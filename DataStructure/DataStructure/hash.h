#pragma once
#include <iostream>
#include <string>

using namespace std;

template<class K>
class hash;

template<>
class hash<string>
{
public:
	size_t operator()(const string theKey) const
	{
		// Convert theKey to a nonnegative integer.
		unsigned long hashValue = 0;
		int length = (int)theKey.length();
		for (int i = 0; i < length; i++)
			hashValue = 5 * hashValue + theKey.at(i);

		return size_t(hashValue);
	}
};

template<>
class hash<int>
{
public:
	size_t operator()(const int theKey) const
	{
		return size_t(theKey);
	}
};

template<>
class hash<long>
{
public:
	size_t operator()(const long theKey) const
	{
		return size_t(theKey);
	}
};
