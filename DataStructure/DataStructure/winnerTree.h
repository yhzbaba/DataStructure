#pragma once

template<class T>
class winnerTree
{
public:
	virtual ~win() {}
	virtual void initialize(T* thePlayer, int theNumberOfPlayers) = 0;
			//用数组thePlayer[1:numberOfPlayers]生成赢者树
	virtual int winner() const = 0;
			//返回赢者的索引
	virtual void rePlay(int thePlayerID, T thePlayer) = 0;
			//在参赛者thePlayer的分数变化后重赛
};