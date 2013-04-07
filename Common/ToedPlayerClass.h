// ToedPlayerClass.h
// Base Class for all player types

#ifndef TOEDPLAYERCLASS_H
#define TOEDPLAYERCLASS_H

#include <string>

#include "..\Common\ToedBoardClass.h"

using namespace std;

class ToedPlayer
{
public:
	ToedPlayer(bool isHuman, char pNum);
	virtual char chooseMove(ToedBoard inBoard)=0;  //on second thought is this needed?  Might only be needed for the ai player.
	
	char m_selectedMove;	//what move did the human/ai make? used in the main loop.
	bool m_isHuman;		//human or computer.

protected:
	char m_Symbol; //1 or 2...virtual x and o
	string m_pName;
	
};

#endif