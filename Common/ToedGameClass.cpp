//ToedGameClass.cpp

#include <Windows.h> ///temp need to get rid of this when making it non OS dependant 
#include <algorithm>
#include <time.h>

#include "..\Common\ToedGameClass.h"
#include "..\Toed\ToedWinGUIPlayerClass.h"
#include "..\Common\ToedAIPlayerClass.h"

using namespace std;

ToedGame::ToedGame()
{
	//first initialize the pointers to the players.	
	m_Players[0] = nullptr;
	m_Players[1] = nullptr;
	m_Winner = -1;
}

ToedGame::~ToedGame()
{
	//free up heap memory for players.
	if(m_Players[0]!=nullptr)
		delete m_Players[0];
	if(m_Players[1]!=nullptr)
		delete m_Players[1];
}

void ToedGame::BeginGame(char nPlayers)
{
	//free up heap memory for players.
	if(m_Players[0]!=nullptr)
		delete m_Players[0];
	if(m_Players[1]!=nullptr)
		delete m_Players[1];
	
	m_Winner = -1;
	m_Board.Reset();
	m_nPlayers=nPlayers;  //store number of players
	
	if (nPlayers==2)
	{
		m_Players[0] = new ToedWinGUIPlayer(1);
		m_Players[1] = new ToedWinGUIPlayer(2);
		m_pTurn = 0;		
		
		return;
	}
	else if(nPlayers==1)
	{
		int rNum;
		srand (time(NULL));

		rNum = rand()% 2;
		if(rNum ==0)
		{
			m_Players[0] = new ToedWinGUIPlayer(1);
			m_Players[1] = new ToedAIPlayer(2);
		}
		else
		{
			m_Players[1] = new ToedWinGUIPlayer(2);
			m_Players[0] = new ToedAIPlayer(1);
		}
		m_pTurn = 0;
		
		//if(!m_Players[0]->m_isHuman)
			//ChooseSpace(m_Players[0]->chooseMove(m_Board));  //if not human decide first move.

		return;
	}
}

void ToedGame::PlayAgain()
{
	BeginGame(m_nPlayers);
}

//Choose space function.  Returns true if empty
bool ToedGame::isSpaceEmpty(char cSpace)
{
	if (m_Board.GetSpaceValue(cSpace) == 0)
		return true;
	else
		return false;
}

//Choose space function.  Returns true if valid 
bool ToedGame::ChooseSpace(char cSpace)
{
	if (isSpaceEmpty(cSpace))
	{
		int tempTurn = m_pTurn;
		m_Board.SetSpaceValue(cSpace,tempTurn+1);
		
		return true;
	}
	else
		return false;	//invalid move
}

char ToedGame::GetGameBoardSpaceValue(char cSpace)
{
	return m_Board.GetSpaceValue(cSpace);
}

bool ToedGame::CheckEnd()
{
	//Are three spaces in a row the same value (that is not 0).  If so someone won.
	if( 
		((m_Board.GetSpaceValue(0)==m_Board.GetSpaceValue(1)) && (m_Board.GetSpaceValue(1)==m_Board.GetSpaceValue(2)) && (m_Board.GetSpaceValue(0)!=0) ) ||
		((m_Board.GetSpaceValue(3)==m_Board.GetSpaceValue(4)) && (m_Board.GetSpaceValue(4)==m_Board.GetSpaceValue(5)) && (m_Board.GetSpaceValue(3)!=0) ) ||
		((m_Board.GetSpaceValue(6)==m_Board.GetSpaceValue(7)) && (m_Board.GetSpaceValue(7)==m_Board.GetSpaceValue(8)) && (m_Board.GetSpaceValue(6)!=0) ) ||
		((m_Board.GetSpaceValue(0)==m_Board.GetSpaceValue(3)) && (m_Board.GetSpaceValue(3)==m_Board.GetSpaceValue(6)) && (m_Board.GetSpaceValue(0)!=0) ) ||
		((m_Board.GetSpaceValue(1)==m_Board.GetSpaceValue(4)) && (m_Board.GetSpaceValue(4)==m_Board.GetSpaceValue(7)) && (m_Board.GetSpaceValue(1)!=0) ) ||
		((m_Board.GetSpaceValue(2)==m_Board.GetSpaceValue(5)) && (m_Board.GetSpaceValue(5)==m_Board.GetSpaceValue(8)) && (m_Board.GetSpaceValue(2)!=0) ) ||
		((m_Board.GetSpaceValue(0)==m_Board.GetSpaceValue(4)) && (m_Board.GetSpaceValue(4)==m_Board.GetSpaceValue(8)) && (m_Board.GetSpaceValue(0)!=0) ) ||
		((m_Board.GetSpaceValue(6)==m_Board.GetSpaceValue(4)) && (m_Board.GetSpaceValue(4)==m_Board.GetSpaceValue(2)) && (m_Board.GetSpaceValue(6)!=0) )		
		)
	{
		m_Winner = m_pTurn;
		//MessageBox(NULL,(LPCWSTR)L"Three in a row",NULL,MB_OK);
		return true;
	}
	else if( m_Board.isFull() )
	{
		m_Winner = -1;
		return true;
	}
	else
		return false;

}

bool ToedGame::GameLogic()
{
	if(m_Players[m_pTurn]->m_selectedMove == -1) // if player (human or ai) hasn't choosen a move, see if it wants to choose one.
		m_Players[m_pTurn]->m_selectedMove = m_Players[m_pTurn]->chooseMove(m_Board); //if human it will set selectedMove to -1, if ai return its move
	
	if(m_Players[m_pTurn]->m_selectedMove!=-1) //if player (human or ai) has selected a move
	{
		if(ChooseSpace(m_Players[m_pTurn]->m_selectedMove))
		{
			//successfully made move
			m_Players[m_pTurn]->m_selectedMove = -1;  //set selected move to none again.
			//m_pTurn = !m_pTurn;  //switch players
			return true;
		}
		else
			//invalid move...reset selected move but don't change player turn.
		{
			m_Players[m_pTurn]->m_selectedMove = -1;
			return false;
		}
			
	}
	
	//else  
		 

	return false;
}

void ToedGame::setSelectedMove(char cSpace)
{
	m_Players[m_pTurn]->m_selectedMove = cSpace;
}

char ToedGame::GetWinner()
{
	return m_Winner;
}

