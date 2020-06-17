#pragma once

#include "Grobal.h"
#include "WinBase.h"

class MyWin :
	public WinBase
{
private:
	POINT	m_MousePos	= {};
	RECT	m_MouseRect = {};

private:
	//	갱신
	VOID	Update();
	//	그리기
	VOID	Render(HDC _hdc);
	//	메시지
	LRESULT WndProc(HWND _hWnd, UINT _message, WPARAM _wParam, LPARAM _lParam);
public:
	MyWin();
	~MyWin();
};

