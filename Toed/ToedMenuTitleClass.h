#ifndef TOEDMENUTITLECLASS_H
#define TOEDMENUTITLECLASS_H

#include <string>

using namespace std;

class ToedMenuTitle
{
public:
	LPCWSTR m_Text;
	int m_textSize;
	LPCWSTR m_fontName;
	bool m_Italic;
	RECT m_Pos;
	COLORREF m_textColor;
	
protected:
};

#endif