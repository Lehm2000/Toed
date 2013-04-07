#ifndef TOEDWINGUIPLAYERCLASS_H
#define TOEDWINGUIPLAYERCLASS_H

#include "..\Common\ToedPlayerClass.h"

class ToedWinGUIPlayer : public ToedPlayer
{
public:
	ToedWinGUIPlayer();
	ToedWinGUIPlayer(char pNum);  //constructor with player number specified.
	virtual char chooseMove(ToedBoard inBoard);

protected:
};

#endif