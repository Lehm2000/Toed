

#include "..\Common\ToedPlayerClass.h"

ToedPlayer::ToedPlayer(bool isHuman=true, char pNum=0)
{
	m_isHuman = isHuman;
	m_Symbol = pNum;
	m_selectedMove = -1;  //initialize to no move.
}