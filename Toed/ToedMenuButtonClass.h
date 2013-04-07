#ifndef TOEDMENUBUTTONCLASS_H
#define TOEDMENUBUTTONCLASS_H

#include <string>

using namespace std;

class ToedMenuButton
{
public:
	LPCWSTR m_Text;
	RECT m_Pos;
	char m_Action;
protected:
};

#endif