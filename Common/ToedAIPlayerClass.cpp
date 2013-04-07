#include <cmath>

#include "..\Common\ToedAIPlayerClass.h"

ToedAIPlayer::ToedAIPlayer():ToedPlayer(false,0)
{

}
ToedAIPlayer::ToedAIPlayer(char pNum):ToedPlayer(false,pNum)
{

}

char ToedAIPlayer::chooseMove(ToedBoard inBoard)
{
	float tempScores[9];
	int choosenMove =0;
	float choosenMoveScore =-1.0;
	for(int i=0;i<9;i++)
	{
		
		if(inBoard.GetSpaceValue(i)==0)
		{
			//ToedBoard tempBoard = inBoard;			//create a temporary board	
			//tempBoard.SetSpaceValue(i,m_Symbol);	//fill in space with player number
			int oTurn;
			if (m_Symbol==1)
				oTurn = 2;
			else
				oTurn = 1;
			tempScores[i]=evalMove(inBoard,i,m_Symbol,1);

			if (tempScores[i]>choosenMoveScore)
			{
				choosenMove = i;
				choosenMoveScore = tempScores[i];
			}
		}
		else
			tempScores[i]=0.0;
			//return i;
	}
	
	return choosenMove; 
}

float ToedAIPlayer::evalMove(ToedBoard inBoard, char sMove,char wTurn,int nIter)
{
	
	
	inBoard.SetSpaceValue(sMove,wTurn);

	//now check to see if that move ended the game.
	int iWinner;
	iWinner = CheckEnd(inBoard);
			
	if(iWinner)
	{
		//there is a winner.
		if(iWinner == m_Symbol)  //if winner is this player
		{
			return 1.0/(pow(10.0,nIter)/10);  //player won,move gets a score of 2.
		}
		else
			return -1.0/(pow(10.0,nIter)/10);  //player lost, move gets score of 0
	}
	else if(inBoard.isFull())
	{
		return 0.0;///(nIter*nIter);		//game ended tied.
	}
	else //no winner and gameboard not full...so game must be continuing.
	{
		float totalScore = 0.0;
		
		for(int i=0;i<9;i++)
		{
			if(inBoard.GetSpaceValue(i)==0)
			{
				//found available space
				//inBoard.SetSpaceValue(i,wTurn);
				
				
				int oTurn;
				if (wTurn==1)
					oTurn = 2;
				else
					oTurn = 1;
				totalScore+= evalMove(inBoard,i, oTurn,nIter+1);

			}

		}
		return totalScore;
	}
	return 0.0;// I don't think it should ever get here.
	
}

char ToedAIPlayer::CheckEnd(ToedBoard inBoard)
{
	//Are three spaces in a row the same value (that is not 0).  If so someone won.
	if( (inBoard.GetSpaceValue(0)==inBoard.GetSpaceValue(1)) && (inBoard.GetSpaceValue(1)==inBoard.GetSpaceValue(2)) && (inBoard.GetSpaceValue(0)!=0) )
		return inBoard.GetSpaceValue(0);
	else if( (inBoard.GetSpaceValue(3)==inBoard.GetSpaceValue(4)) && (inBoard.GetSpaceValue(4)==inBoard.GetSpaceValue(5)) && (inBoard.GetSpaceValue(3)!=0) )
		return inBoard.GetSpaceValue(3);
	else if( (inBoard.GetSpaceValue(6)==inBoard.GetSpaceValue(7)) && (inBoard.GetSpaceValue(7)==inBoard.GetSpaceValue(8)) && (inBoard.GetSpaceValue(6)!=0) )
		return inBoard.GetSpaceValue(6);
	else if( (inBoard.GetSpaceValue(0)==inBoard.GetSpaceValue(3)) && (inBoard.GetSpaceValue(3)==inBoard.GetSpaceValue(6)) && (inBoard.GetSpaceValue(0)!=0) )
		return inBoard.GetSpaceValue(0);
	else if( (inBoard.GetSpaceValue(1)==inBoard.GetSpaceValue(4)) && (inBoard.GetSpaceValue(4)==inBoard.GetSpaceValue(7)) && (inBoard.GetSpaceValue(1)!=0) )
		return inBoard.GetSpaceValue(1);
	else if( (inBoard.GetSpaceValue(2)==inBoard.GetSpaceValue(5)) && (inBoard.GetSpaceValue(5)==inBoard.GetSpaceValue(8)) && (inBoard.GetSpaceValue(2)!=0) )
		return inBoard.GetSpaceValue(2);
	else if( (inBoard.GetSpaceValue(0)==inBoard.GetSpaceValue(4)) && (inBoard.GetSpaceValue(4)==inBoard.GetSpaceValue(8)) && (inBoard.GetSpaceValue(0)!=0) )
		return inBoard.GetSpaceValue(0);
	else if( (inBoard.GetSpaceValue(6)==inBoard.GetSpaceValue(4)) && (inBoard.GetSpaceValue(4)==inBoard.GetSpaceValue(2)) && (inBoard.GetSpaceValue(6)!=0) )
		return inBoard.GetSpaceValue(6);
	else
		return 0;  //no winner.
	

}