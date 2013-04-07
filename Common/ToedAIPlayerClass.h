#ifndef TOEDAIPLAYERCLASS_H
#define TOEDAIPLAYERCLASS_H

#include "..\Common\ToedPlayerClass.h"

class ToedAIPlayer : public ToedPlayer
{
public:
	//constructors.
	ToedAIPlayer();
	ToedAIPlayer(char pNum); //constructor with player number spec'd
	
	//class functions
	virtual char chooseMove(ToedBoard inBoard);
	float evalMove(ToedBoard inBoard,char sMove, char wTurn, int nIter);  //recursion function for deciding move, gets copy of board and whose turn it is.
	char CheckEnd(ToedBoard inBoard);  //check for end of game
protected:
};

#endif