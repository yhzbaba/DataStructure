#pragma once

template<class T>
class winnerTree
{
public:
	virtual ~win() {}
	virtual void initialize(T* thePlayer, int theNumberOfPlayers) = 0;
			//������thePlayer[1:numberOfPlayers]����Ӯ����
	virtual int winner() const = 0;
			//����Ӯ�ߵ�����
	virtual void rePlay(int thePlayerID, T thePlayer) = 0;
			//�ڲ�����thePlayer�ķ����仯������
};