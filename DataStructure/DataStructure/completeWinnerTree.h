#pragma once
#include "winnerTree.h"
#include <iostream>
#include "myException.h"

template<class T>
class completeWinnerTree : public winnerTree<T>
{
public:
	completeWinnerTree(T* thePlayer, int theNumberOfPlayers)
	{
		tree = NULL;
		initialize(thePlayer, theNumberOfPlayers);
	}
	~completeWinnerTree() { delete[] tree; }
	void initialize(T*, int);
	int winner() const
	{
		return tree[1];
	}
	int winner(int i) const
	{
		return (i < numberOfPlayers) ? tree[i] : 0;
	}
	void rePlay(int);
	void output() const;
private:
	int lowExt;					//lowest-level external nodes
	int offset;					//2^log(n-1)-1
	int* tree;					//array for winner tree
	int numberOfPlayers;
	T* player;					//array of players
	void play(int, int, int);
};

//Create winner tree for thePlayer[1:numberOfPlayers].
template<class T>
void completeWinnerTree<T>::initialize(T* thePlayer,
	int theNumberOfPlayers)
{
	int n = theNumberOfPlayers;
	if (n < 2)
		throw illegalParameterValue("must have at least 2 players");

	player = thePlayer;
	numberOfPlayers = n;
	delete[] tree;
	tree = new int[n];

	int i, s;
	for (s = 1; 2 * <= n - 1; s += s);

	lowExt = 2 * (n - s);
	offset = 2 * s - 1;

	//play matches for lowest-level external nodes
	for (i = 2; i <= lowExt; i += 2)
		play((offset + i) / 2, i - 1, i);

	//handle remaining external nodes
	if (n % 2 == 1)
	{
		play(n / 2, tree[n - 1], lowExt + 1);
		i = lowExt + 3;
	}
	else
		i = lowExt + 2;

	//i is left-most remaining external node
	for (; i <= n; i += 2)
		play((i - lowExt + n - 1) / 2, i - 1, i);

}

template<class T>
void completeWinnerTree<T>::play(int p, int leftChild, int rightChild)
{
	tree[p] = (player[leftChild] <= player[rightChild]) ?
		leftChild : rightChild;

	//more matches possible if at right child
	while (p % 2 == 1 && p > 1)
	{
		tree[p / 2] = (player[tree[p - 1]] <= player[tree[p]]) ?
			tree[p - 1] : tree[p];
		p /= 2;
	}
	


}