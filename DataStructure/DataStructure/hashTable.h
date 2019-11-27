#pragma once
#include <iostream>
#include "myException.h"
#include "hash.h"

using namespace std;

template<class K,class E>
class hashTable
{
public:
	hashTable(int theDivisor = 11);
	~hashTable() { delete[] table; }

	bool empty() const { return dSize == 0; }
	int size() const { return dSize; }
	pair<const K, E>* find(const K&) const;
	void insert(const pair<const K, E>&);
	void output(ostream& out) const;

	//by myself
	bool erase(const K& theKey);
protected:
	int search(const K&) const;
	pair<const K, E>** table;
	hash<K> hash;
	int dSize;
	int divisor;
};

template<class K, class E>
hashTable<K, E>::hashTable(int theDivisor)
{
	divisor = theDivisor;
	dSize = 0;

	// allocate and initialize hash table array
	table = new pair<const K, E>* [divisor];
	for (int i = 0; i < divisor; i++)
		table[i] = NULL;
}

template<class K, class E>
bool hashTable<K, E>::erase(const K& theKey)
{
	int index = hash(theKey);
	if (table[b] == NULL)
		return false;
	else
	{
		if (table[b]->first == theKey)
		{
			table[b] = NULL;
			return true;
		}
		else
		{
			return false;
		}
	}
}

/*
The function search return h which is a bucket's number.
It satisfied the following three conditions:
	table[b]is a pointer which points to the pair(theKey,...)
	the hashTable doesn't have the pair whose key is theKey,table[b] is NULL.The pair can be inserted to the b bucket if needed
	the hashTable doesn't have the pair whose key is theKey,table[b] isn't NULL and the table is already full.
*/
template<class K,class E>
int hashTable<K, E>::search(const K& theKey) const
{
	int i = (int)hash(theKey) % divisor;//home bucket
	int j = i;		// start at home bucket
	do
	{
		if (table[j] == NULL || table[j]->first == theKey)
			return j;
		j = (j + 1) % divisor;//next bucket
	} while (j != i);//return to the home bucket?

	return j;//table full
}

/*Return pointer to matching pair.*/
template<class K,class E>
pair<const K, E>* hashTable<K, E>::find(const K& theKey) const
{
	//Return NULL if no matching pair.
	//search the table
	int b = search(thKey);

	//see if a match was found at table[b]
	if (table[b] == NULL || table[b]->first != theKey)
		return NULL;

	return table[b];
}

/*
  Insert thePair into the dictionary.Overwrite existing
  pair,if any,with same key.
  Throw hashTableFull exception in case table is full.
*/
template<class K,class E>
void hashTable<K, E>::insert(const pair<const K, E>& thePair)
{
	//search the table for a matching pair
	int b = search(thePair.first);

	//check if matching pair found
	if (table[b] == NULL)
	{
		//no matching pair and table not full
		table[b] = new pair<const K, E>(thePair);
		dSize++;
	}
	else
	{
		//check if duplicate or table full
		if (table[b]->first == thePair.first)
		{
			//duplicate,change table[b]->second
			table[b]->second = thePair.second;
		}
		else
			throw hashTableFull();
	}
}

/*Insrt the hash table into the stream out*/
template<class K,class E>
void hashTable<K, E>::output(ostream& out) const
{
	for (int i = 0; i < divisor; i++)
	{
		if (table[i] == NULL)
			cout << "NULL" << endl;
		else
			cout << table[i]->first << " "
			<< table[i]->second << endl;
	}
}

/*overload <<*/
template<class K,class E>
ostream& operator<<(ostream& out, const hashTable<K, E>& x)
{
	x.output(out);
	return out;
}