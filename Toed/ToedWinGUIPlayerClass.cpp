

#include "ToedWinGUIPlayerClass.h"

ToedWinGUIPlayer::ToedWinGUIPlayer():ToedPlayer(true,0)
{

}

ToedWinGUIPlayer::ToedWinGUIPlayer(char pNum):ToedPlayer(true,pNum)
{

}

char ToedWinGUIPlayer::chooseMove(ToedBoard inBoard)
{
	return -1;  // aka game should wait for player input...I hope this is the correct way to go about it.
}