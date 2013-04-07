#ifndef TOEDWINMENUCLASS_H
#define TOEDWINMENUCLASS_H

#include <Windows.h>
#include <vector>

#include "ToedMenuButtonClass.h"
#include "ToedMenuTitleClass.h"

class ToedWinMenu
{
public:
	bool AddButton(LPCWSTR buttonText,RECT posCoords,char buttonAction);				//add button to menu
	bool AddTitle(LPCWSTR titleText, RECT posCoords, int fontSize,LPCWSTR fontName,COLORREF tColor, bool isItalic);	//add title to menu, return true if successful
	bool ClearTitles();					//removes all titles from menus.  Good for when they need to be dynamic.
	//void UpdateTitle();				//not sure how this one will work yet.
	void DrawMenu(HWND hWnd);			//Draw the menu.
	char Clicked(int x, int y);		//menu was clicked return action if any.
	void SetBackgroundColor(COLORREF inColor);
	bool isOverButton(int x, int y);

protected:
	vector<ToedMenuButton> m_menuButtons;
	vector<ToedMenuTitle> m_menuTitles;
	COLORREF m_backColor;
};

#endif