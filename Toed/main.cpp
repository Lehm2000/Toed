
#include <Windows.h>

#include <string>

#include "resource.h"
#include "..\Common\ToedGameClass.h"
#include "..\Common\Toed_Constants.h"
#include "ToedWinMenuClass.h"

//=============================================
//Global Variables

ToedGame myGame;

ToedWinMenu mainMenu;
ToedWinMenu postMenu;


char gameMode=TOED_MAINMENU;  //Menu, Play etc.

POINT lastMousePos = {-1,-1};


//=============================================
//Function definitions

LRESULT CALLBACK WindowProc(HWND hWnd,UINT message, WPARAM wParam,LPARAM lParam);

//=============================================
//Main Code

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASSEX WindowClass;

	static LPCTSTR szAppName = L"Toed";
	HWND hWnd;
	MSG msg;
	
	WindowClass.cbSize = sizeof(WNDCLASSEX);
	WindowClass.style = CS_HREDRAW | CS_VREDRAW;
	WindowClass.lpfnWndProc = WindowProc;
	WindowClass.cbClsExtra = 0;
	WindowClass.cbWndExtra = 0;
	WindowClass.hInstance = hInstance;
	WindowClass.hIcon = LoadIcon(hInstance,IDI_ICONTOEDMY01);
	WindowClass.hCursor = LoadCursor(0, IDC_ARROW);
	WindowClass.hbrBackground = static_cast<HBRUSH>(GetStockObject(WHITE_BRUSH));
	WindowClass.lpszMenuName = 0;
	WindowClass.lpszClassName = szAppName;
	WindowClass.hIconSm = 0;

	RegisterClassEx(&WindowClass);

	//========================================
	//Create Window
	//========================================
	
	LPRECT wndSize=new RECT;
	wndSize->top =0;
	wndSize->left =0;
	wndSize->bottom=300;
	wndSize->right=300;
	DWORD wndStyle = WS_BORDER | WS_SYSMENU |WS_CAPTION ;
	AdjustWindowRect(wndSize, wndStyle,false);
	
	hWnd = CreateWindow(szAppName, L"Toed", wndStyle,CW_USEDEFAULT,CW_USEDEFAULT,wndSize->right-wndSize->left,wndSize->bottom-wndSize->top,0,0,hInstance,0);

	ShowWindow(hWnd, nCmdShow);
	
	

	//now that the window is setup do game stuff
	
	//==================================================
	//Create Menus
	//==================================================
	RECT workingRect;
	
	mainMenu.SetBackgroundColor(RGB(255,255,255));
	workingRect.left = 0;workingRect.right = 300;workingRect.top =0;workingRect.bottom=30;
	mainMenu.AddTitle(L"TOED",workingRect,32,L"BankGothic Md BT",RGB(255,0,0),true);

	workingRect.left = 50; workingRect.right = 250; workingRect.top = 150; workingRect.bottom = 180;
	mainMenu.AddButton(L"1 Player",workingRect,TOED_MENUACTION_PLAYGAME1);
	workingRect.left = 50; workingRect.right = 250; workingRect.top = 200; workingRect.bottom = 230;
	mainMenu.AddButton(L"2 Player",workingRect,TOED_MENUACTION_PLAYGAME2);
	//workingRect.left = 50; workingRect.right = 250; workingRect.top = 250; workingRect.bottom = 280;
	//mainMenu.AddButton(L"No Player",workingRect,TOED_MENUACTION_PLAYGAME2);
	
	postMenu.SetBackgroundColor(RGB(255,255,255));
	workingRect.left = 50; workingRect.right=250; workingRect.top = 150; workingRect.bottom = 180;
	postMenu.AddButton(L"Play Again",workingRect,TOED_MENUACTION_PLAYGAME);
	workingRect.left = 50; workingRect.right=250; workingRect.top = 200; workingRect.bottom = 230;
	postMenu.AddButton(L"Main Menu",workingRect,TOED_MENUACTION_MAINMENU);

	
	
	//temp jump right into game...eventually need menu.
	
	gameMode = TOED_MAINMENU; 
	myGame.BeginGame();
	
	//once the game is setup force window update
	UpdateWindow(hWnd);
	
	/*while(GetMessage(&msg,0,0,0)==TRUE)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}*/
	while(true)
    {
		if(PeekMessage(&msg,NULL,0,0,PM_REMOVE))
		{
			if(msg.message == WM_QUIT)
				break;
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			//game code
			bool madeMove;
			
			if(gameMode == TOED_PLAY)
			{
				madeMove = myGame.GameLogic();  //takes what the player human or ai decided to do and uses it...if move is legal.

				if(myGame.CheckEnd() ) //is game over?
				{
								
					//we have a winner
					gameMode = TOED_POSTGAME;

					//update the postgame menu.
					postMenu.ClearTitles();	//get rid of existing titles so the correct info can be displayed.

					//input new titles
					workingRect.left = 0; workingRect.right=300; workingRect.top = 0; workingRect.bottom = 64;
					LPCWSTR winnerString;
					if(myGame.GetWinner() ==-1)
						winnerString = L"Tied Game";
					else
						winnerString = L"Winner!";
					postMenu.AddTitle(winnerString,workingRect,24,L"BankGothic Md BT",RGB(0,0,0),false);
				
					//strlen(winnerString);

					if(myGame.GetWinner()==0)
						winnerString = L"Player1";
					else if(myGame.GetWinner()==1)
						winnerString = L"Player2";
					else
						winnerString = L"No One Wins";
					workingRect.left = 0; workingRect.right=300; workingRect.top = 48; workingRect.bottom = 80;
					postMenu.AddTitle(winnerString,workingRect,40,L"BankGothic Md BT",RGB(255,0,0),true);
					//finished update postgame menu.
				}
				if(madeMove)
				{
					myGame.m_pTurn = !myGame.m_pTurn;
					InvalidateRect(hWnd,NULL,false);  //force redraw to update so player move shows up.
					
				}
			}
			
		}
	}


	return static_cast<int>(msg.wParam);

}

LRESULT CALLBACK WindowProc(HWND hWnd,UINT message, WPARAM wParam,LPARAM lParam)
{
	HDC hDC;
	PAINTSTRUCT PaintSt;
	RECT aRect;

	POINT curPos = { LOWORD(lParam) , HIWORD(lParam) };
	POINT workingCoords;
	RECT workingRect;

	//convert the coordinates to a space on the board.

	POINT spacePos = { lastMousePos.x/100,lastMousePos.y/100};
	char gameSpace = (spacePos.y*3)+spacePos.x;

	HPEN workingPen,hiLightPen;
	//HGDIOBJ oldPen;
	

	switch(message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_ERASEBKGND:
        return (LRESULT)1;  //background never gets erased.
	
	case WM_PAINT:
		
		if(gameMode == TOED_PLAY)
		{
			HDC hdcMem;
			HBITMAP hbmMem, hbmOld;
			
			int scaleFactor = 4;  //for antialiasing.

			hDC = BeginPaint(hWnd, &PaintSt);
			GetClientRect(hWnd, &aRect);
			
			hdcMem = CreateCompatibleDC(PaintSt.hdc);
			hbmMem = CreateCompatibleBitmap(PaintSt.hdc, (aRect.right-aRect.left)*scaleFactor,(aRect.bottom-aRect.top)*scaleFactor);

			hbmOld = (HBITMAP)SelectObject(hdcMem,hbmMem);

			SelectObject(hdcMem,GetStockObject(NULL_PEN));
			SelectObject(hdcMem,GetStockObject(WHITE_BRUSH));
			Rectangle(hdcMem,0,0,aRect.right*scaleFactor,aRect.bottom*scaleFactor);
		
			//Draw Highlight
			if(!myGame.GetGameBoardSpaceValue(gameSpace))  //if space isnt filled
			{
				//get coordinates of space.
				workingCoords.x=spacePos.x;
				workingCoords.y=spacePos.y;
				workingRect.top = (workingCoords.y*100)*scaleFactor;
				workingRect.bottom = ((workingCoords.y+1)*100)*scaleFactor;
				workingRect.left = (workingCoords.x*100)*scaleFactor;
				workingRect.right = ((workingCoords.x+1)*100)*scaleFactor;

				InflateRect(&workingRect,-10 * scaleFactor,-10 * scaleFactor);
				
				SelectObject(hdcMem,GetStockObject(NULL_BRUSH));
				hiLightPen = CreatePen(PS_SOLID,5*scaleFactor,RGB(255,0,0));
				SelectObject(hdcMem,hiLightPen);

				//Rectangle(hDC,workingRect.x*100,spacePos.y*100,(spacePos.x+1)*100,(spacePos.y+1)*100);

				if (myGame.m_pTurn == 0)
				{
					MoveToEx(hdcMem,workingRect.left,workingRect.top,0);LineTo(hdcMem,workingRect.right,workingRect.bottom);
					MoveToEx(hdcMem,workingRect.left,workingRect.bottom,0);LineTo(hdcMem,workingRect.right,workingRect.top);
					//Ellipse(hDC,workingRect.left,workingRect.top,workingRect.right,workingRect.bottom);
				}
				else
				{
					Ellipse(hdcMem,workingRect.left,workingRect.top,workingRect.right,workingRect.bottom);
				}
				DeleteObject(hiLightPen);
				SelectObject(hdcMem,GetStockObject(NULL_BRUSH));
			}
		
			workingPen = CreatePen(PS_SOLID,5*scaleFactor,RGB(0,0,0));

			SelectObject(hdcMem,workingPen);
			//Draw Board;
			MoveToEx(hdcMem,100 * scaleFactor,0,0);LineTo(hdcMem,100 * scaleFactor,300 * scaleFactor);
			MoveToEx(hdcMem,200 * scaleFactor,0,0);LineTo(hdcMem,200 * scaleFactor,300 * scaleFactor);

			MoveToEx(hdcMem,0,100 * scaleFactor,0);LineTo(hdcMem,300 * scaleFactor,100 * scaleFactor);
			MoveToEx(hdcMem,0,200 * scaleFactor,0);LineTo(hdcMem,300 * scaleFactor,200 * scaleFactor);

			//now draw board values;
			for (int i=0;i<10;i++)
			{
				//get coordinates of space.
				workingCoords.x=i%3;
				workingCoords.y=i/3;
				workingRect.top = (workingCoords.y*100) * scaleFactor;
				workingRect.bottom = ((workingCoords.y+1)*100) * scaleFactor;
				workingRect.left = (workingCoords.x*100) * scaleFactor;
				workingRect.right = ((workingCoords.x+1)*100) * scaleFactor;

				InflateRect(&workingRect,-10 * scaleFactor,-10 * scaleFactor);
					

				char spaceValue = myGame.GetGameBoardSpaceValue(i);

				if (spaceValue == 1)
				{
					MoveToEx(hdcMem,workingRect.left,workingRect.top,0);LineTo(hdcMem,workingRect.right,workingRect.bottom);
					MoveToEx(hdcMem,workingRect.left,workingRect.bottom,0);LineTo(hdcMem,workingRect.right,workingRect.top);
					//Ellipse(hDC,workingRect.left,workingRect.top,workingRect.right,workingRect.bottom);
				}
				else if(spaceValue == 2)
				{
					Ellipse(hdcMem,workingRect.left,workingRect.top,workingRect.right,workingRect.bottom);
				}

			}
			
			DeleteObject(workingPen);

			//copy image in memory to the screen
			SetStretchBltMode(hdcMem,HALFTONE);
			SetStretchBltMode(PaintSt.hdc,HALFTONE);
			StretchBlt(PaintSt.hdc,aRect.left,aRect.top,aRect.right-aRect.left,aRect.bottom-aRect.top,hdcMem,aRect.left * scaleFactor,aRect.top * scaleFactor,(aRect.right-aRect.left) * scaleFactor,(aRect.bottom-aRect.top) * scaleFactor,SRCCOPY);
			//BitBlt(PaintSt.hdc,aRect.left,aRect.top,aRect.right-aRect.left,aRect.bottom-aRect.top,hdcMem,0,0,SRCCOPY);

			SelectObject(hdcMem,hbmOld);
			DeleteObject(hbmMem);
			DeleteDC(hdcMem);

			EndPaint(hWnd, &PaintSt);
			
		}
		else if(gameMode == TOED_POSTGAME)
		{
			//draw the menu.
			postMenu.DrawMenu(hWnd);
			
		}
		else if(gameMode == TOED_MAINMENU)
		{
			mainMenu.DrawMenu(hWnd);
		}
		
		return 0;
	case WM_MOUSEMOVE:
		
		lastMousePos.x = curPos.x;
		lastMousePos.y = curPos.y;

		if(gameMode == TOED_PLAY)
		{
			if (myGame.GetGameBoardSpaceValue(gameSpace)==0)
			{
				SetCursor(LoadCursor(0,IDC_HAND));
			}
			else
			{
				SetCursor(LoadCursor(0,IDC_ARROW));
			}
			
		}
		else if(gameMode == TOED_POSTGAME)
		{
			if(postMenu.isOverButton(curPos.x,curPos.y))
			{
				SetCursor(LoadCursor(0,IDC_HAND));
			}
			else
			{
				SetCursor(LoadCursor(0,IDC_ARROW));
			}
		}
		else if(gameMode == TOED_MAINMENU)
		{
			if(mainMenu.isOverButton(curPos.x,curPos.y))
			{
				SetCursor(LoadCursor(0,IDC_HAND));
			}
			else
			{
				SetCursor(LoadCursor(0,IDC_ARROW));
			}
		}
		InvalidateRect(hWnd,NULL,false);  //force redraw
		return 0;

	case WM_LBUTTONUP:
		if(gameMode == TOED_PLAY)
		{
			//myGame.ChooseSpace(gameSpace);
			myGame.setSelectedMove(gameSpace);
			
			InvalidateRect(hWnd,NULL,false);	//force redraw.
			//myGame.GetGameBoardSpaceValue(gameSpace);	
		}
		else if(gameMode == TOED_POSTGAME)
		{
			char clickAction;
			clickAction = postMenu.Clicked(curPos.x, curPos.y);
			switch(clickAction)
			{
			case TOED_MENUACTION_PLAYGAME:
				myGame.PlayAgain();
				gameMode = TOED_PLAY;
				InvalidateRect(hWnd,NULL,false);
				break;
			case TOED_MENUACTION_MAINMENU:
				gameMode = TOED_MAINMENU;
				InvalidateRect(hWnd,NULL,false);

			default:
				break;
			}

		}
		else if(gameMode == TOED_MAINMENU)
		{
			char clickAction;
			clickAction = mainMenu.Clicked(curPos.x, curPos.y);
			switch(clickAction)
			{
			case TOED_MENUACTION_PLAYGAME2:
				myGame.BeginGame(2);
				gameMode = TOED_PLAY;
				InvalidateRect(hWnd,NULL,false);
				break;
			case TOED_MENUACTION_PLAYGAME1:
				myGame.BeginGame(1);
				gameMode = TOED_PLAY;
				InvalidateRect(hWnd,NULL,false);
				break;
			default:
				break;
			}

		}


		return 0;

	default:
		return DefWindowProc(hWnd,message,wParam,lParam);
	}
}