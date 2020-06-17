#include "MyWin.h"

VOID MyWin::Update()
{
	SetRect(&m_MouseRect, 0, 0, 100, 100);
	OffsetRect(&m_MouseRect, m_MousePos.x, m_MousePos.y);
}

VOID MyWin::Render(HDC _hdc)
{
	Rectangle(_hdc, 
		m_MouseRect.left, 
		m_MouseRect.top, 
		m_MouseRect.right, 
		m_MouseRect.bottom);
}

LRESULT MyWin::WndProc(HWND _hWnd, UINT _message, WPARAM _wParam, LPARAM _lParam)
{
	switch (_message)
	{
	case WM_MOUSEMOVE:
	{
		m_MousePos.x = GET_X_LPARAM(_lParam);
		m_MousePos.y = GET_Y_LPARAM(_lParam);
	}break;
	}
	return WinBase::WndProc(_hWnd, _message, _wParam, _lParam);
}

MyWin::MyWin()
{
}


MyWin::~MyWin()
{
}
