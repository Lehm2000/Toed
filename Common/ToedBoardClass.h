// ToedBoardClass.h
// Holds all the peices

#ifndef TOEDBOARDCLASS_H
#define TOEDBOARDCLASS_H



class ToedBoard
{
public:
	ToedBoard();
	//~ToedBoard();
	void Reset();

	char GetSpaceValue(char cSpace);  //get value of space on gameboard.
	bool SetSpaceValue(char cSpace,char pValue);  //set value of space on gameboard. Return true if successful
	bool isFull();  //has every space in the board been used.

protected:
	char m_gameBoard[9];  //nine spaces on board
	

};


#endif