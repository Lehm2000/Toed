
#include <string>

#include "ToedWinMenuClass.h"
#include "ToedMenuButtonClass.h"
#include "ToedMenuTitleClass.h"

using namespace std;

bool ToedWinMenu::AddTitle(LPCWSTR titleText, RECT posCoords, int fontSize,LPCWSTR fontName,COLORREF tColor, bool isItalic)
{
	ToedMenuTitle tempTitle;
	
	tempTitle.m_Text = titleText;
	tempTitle.m_Pos = posCoords;
	tempTitle.m_textSize = fontSize;
	tempTitle.m_fontName = fontName;
	tempTitle.m_Italic = isItalic;
	tempTitle.m_textColor = tColor;

	m_menuTitles.push_back(tempTitle);

	return true;
}

bool ToedWinMenu::AddButton(LPCWSTR buttonText,RECT posCoords,char buttonAction)
{
	ToedMenuButton tempButton;
	
	tempButton.m_Text = buttonText;
	tempButton.m_Pos = posCoords;
	tempButton.m_Action = buttonAction;
	
	m_menuButtons.push_back(tempButton);
	
	return true;
}

bool ToedWinMenu::ClearTitles()
{
	m_menuTitles.clear();
	return true;
}

void ToedWinMenu::SetBackgroundColor(COLORREF inColor)
{
	m_backColor = inColor;
}

void ToedWinMenu::DrawMenu(HWND hWnd)
{
	HDC hDC;
	PAINTSTRUCT PaintSt;
	hDC = BeginPaint(hWnd, &PaintSt);
	RECT aRect;
	HFONT oldFont;
	HPEN oldPen;
	GetClientRect(hWnd, &aRect);
	
	//Draw Background.
	SelectObject(hDC,GetStockObject(NULL_PEN));
	SelectObject(hDC,GetStockObject(WHITE_BRUSH));
	//SelectObject(hDC,CreateSolidBrush(RGB(255,0,0)));
	Rectangle(hDC,0,0,aRect.right+1,aRect.bottom+1);
	SelectObject(hDC,GetStockObject(NULL_BRUSH));
	//iterate through the titles and draw them.
	
	for(int i=0;i<m_menuTitles.size();i++)
	{
		HFONT titleFont = CreateFont(m_menuTitles[i].m_textSize,0,0,0,0,m_menuTitles[i].m_Italic,0,0,0,0,0,0,0,m_menuTitles[i].m_fontName);
		oldFont = (HFONT)SelectObject(hDC,titleFont);
		SetTextColor(hDC,m_menuTitles[i].m_textColor);
		DrawText(hDC,m_menuTitles[i].m_Text,wcslen(m_menuTitles[i].m_Text),&m_menuTitles[i].m_Pos,DT_CENTER|DT_VCENTER|DT_SINGLELINE);
		SelectObject(hDC,oldFont);
		DeleteObject(titleFont);
	}

	//iterate through the buttons;
	for(int i=0;i<m_menuButtons.size();i++)
	{
		//DrawOutline
		HPEN borderPen = CreatePen(PS_SOLID,1,RGB(0,0,0));
		oldPen = (HPEN)SelectObject(hDC,borderPen);
		Rectangle(hDC,m_menuButtons[i].m_Pos.left,m_menuButtons[i].m_Pos.top,m_menuButtons[i].m_Pos.right,m_menuButtons[i].m_Pos.bottom);
		SelectObject(hDC,oldPen);
		DeleteObject(borderPen);

		//DrawText
		HFONT buttonFont = CreateFont(18,0,0,0,0,false,0,0,0,0,0,0,0,L"Arial");
		oldFont = (HFONT)SelectObject(hDC,buttonFont);
		DrawText(hDC,m_menuButtons[i].m_Text,wcslen(m_menuButtons[i].m_Text),&m_menuButtons[i].m_Pos,DT_CENTER|DT_VCENTER|DT_SINGLELINE);
		SelectObject(hDC,oldFont);
		DeleteObject(buttonFont);

	}

	EndPaint(hWnd, &PaintSt);
}

bool ToedWinMenu::isOverButton(int x, int y)
{
	for (int i=0;i<m_menuButtons.size();i++)
	{
		if (x > m_menuButtons[i].m_Pos.left && x < m_menuButtons[i].m_Pos.right && y > m_menuButtons[i].m_Pos.top && y < m_menuButtons[i].m_Pos.bottom)
			return true;
	}
	
	return false;
}

char ToedWinMenu::Clicked(int x, int y)
{
	for (int i=0;i<m_menuButtons.size();i++)
	{
		if (x > m_menuButtons[i].m_Pos.left && x < m_menuButtons[i].m_Pos.right && y > m_menuButtons[i].m_Pos.top && y < m_menuButtons[i].m_Pos.bottom)
			return m_menuButtons[i].m_Action;
	}

}

