//œ‰◊”≈≈–Ú
#pragma once
#include <string>
#include <iostream>
#include "chain.h"
using namespace std;


struct studentRecord
{
	int score;
	string* name;

	int operator !=(const studentRecord& x) const
	{
		return (score != x.score);
	}
	operator int()const { return score; }
	
};

ostream& operator<<(ostream& out, const studentRecord& x)
{
	out << x.score << ' ' << *x.name << endl;
	return out;
}

void binSort(chain<studentRecord>& theChain, int range)
{
	//Initial the box.
	chain<studentRecord>* bin;
	bin = new chain<studentRecord>[range + 1];

	//Get the students' information from the chain and distribute them into the boxes.
	int numberOfElements = theChain.size();
	for (int i = 0; i < numberOfElements; i++)
	{
		studentRecord x = theChain.get(0);
		theChain.erase(0);
		bin[x.score].insert(0, x);
	}

	//Get the elements from the boxes.
	for (int j = range; j >= 0; j--)
	{
		while (!bin[j].empty())
		{
			studentRecord x = bin[j].get(0);
			bin[j].erase(0);
			theChain.insert(0, x);
		}
	}

	delete[] bin;
}
