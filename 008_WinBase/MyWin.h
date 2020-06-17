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
	//	����
	VOID	Update();
	//	�׸���
	VOID	Render(HDC _hdc);
	//	�޽���
	LRESULT WndProc(HWND _hWnd, UINT _message, WPARAM _wParam, LPARAM _lParam);
public:
	MyWin();
	~MyWin();
};

