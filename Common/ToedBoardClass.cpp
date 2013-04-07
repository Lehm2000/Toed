// ToedBoardClass.cpp
// 
#include <algorithm>
#include "ToedBoardClass.h"

using namespace std;

ToedBoard::ToedBoard()
{
	fill(m_gameBoard,m_gameBoard+9,0);  //set all the spaces on the board to 0

}

void ToedBoard::Reset()
{
	fill(m_gameBoard,m_gameBoard+9,0);  //set all the spaces on the board to 0
}

// Return what value a space has
char ToedBoard::GetSpaceValue(char cSpace)
{
	
	return m_gameBoard[cSpace];
}

// Set what value a space has.  Return true if successful
bool ToedBoard::SetSpaceValue(char cSpace,char pValue)
{
	m_gameBoard[cSpace]=pValue;
	return true;
		
}

bool ToedBoard::isFull()
{
	bool foundEmpty=false;

	for (int i=0;i<9;i++)
	{
		if(m_gameBoard[i]==0)
			foundEmpty=true;
	}

	return !foundEmpty;  //if found an empty space board is not full.
}