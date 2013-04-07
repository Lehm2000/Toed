// ToedGameClass.h
// Base logic for game

#include "..\Common\ToedBoardClass.h"
#include "..\Common\ToedPlayerClass.h"

#ifndef TOEDGAMECLASS_H
#define TOEDGAMECLASS_H

class ToedGame
{
public:
	ToedGame();
	~ToedGame();
	void BeginGame(char nPlayers=2);
	void PlayAgain();
	bool isSpaceEmpty(char cSpace);  //check if space is empty return true if empty.
	bool ChooseSpace(char cSpace);  //select space to put peice.  Returns true if valid selection.
	char GetGameBoardSpaceValue(char cSpace);
	bool CheckEnd(); //has somebody won the game
	char GetWinner();   //who won the game
	bool GameLogic();   //main game stuff...best name for this?  
	void setSelectedMove(char cSpace);
	bool m_pTurn;  //whose turn is it. 
	

protected:
	ToedBoard m_Board;
	ToedPlayer* m_Players[2];  //Two players x and o
	char m_Winner;				//who won the round.
	char m_nPlayers;			//number of players 
};


#endif