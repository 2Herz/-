#undef UNICODE	//	�����ڵ� ���ڿ��� ������� �ʰڴٴ� �ǹ�
#include <Windows.h>	//	������ ���α׷��ֿ��� ���� �߿��� �������..�̰� ������ �ƹ����� ��Ž..

//	���� ������ â�� ũ�� ���� (�̰� �� �� ���ϵ�󱸿�..����)
#define WIN_WIDTH 800
#define WIN_HEIGHT 600

//	���� ������ ���α׷��� �̸��� �����ϴ� �κ�
LPCSTR g_WindowName = "�⺻������â";

//	�ݹ��Լ�(Call back Function) : ������ �ü���� ��� ȣ�����ִ� �Լ�
//	���ڼ���
//	1. HWND		: ���� �������� �ڵ鰪, �ڵ鿡 ���ؼ��� ���� ����
//	2. UINT		: ���� �����쿡�� �߻��� �޼����� ���� ����
//	3. WPARAM	: �޽����� �����ϴ� WORD�� �Ű�����, �ڵ� or ������ ���޵�
//	4. LPARAM	: �޽����� �����ϴ� LONG�� �Ű�����, �����Ͱ� ����
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	//	������ �ü���� �޼����� �ְ�޴� �������� ���ư��� �ü��.
	//	�� ���� �����쿡�� ó���� �� �ִ� ��� ������ �޼���ó���� ����
	//	����� ������ �ı�(close) �κи� ó���س��� ����
	switch (msg)
	{
		//	Ư�� Ű�� ������ �� �߻��ϴ� �޼���
		case WM_KEYDOWN:
		{
			switch (wParam)
			{
				//	ESCŰ�� ������ �� �߻��ϴ� �޼��� / �����ư
			case VK_ESCAPE:
				PostQuitMessage(0);
				break;

			default:
				break;
			}
		}

		//	������ ���콺��ư�� ������ �� �߻��ϴ� �޼��� / �޼����ڽ�
		case WM_RBUTTONDOWN:
		{
			MessageBox(hWnd, "���� �����Ͻðڽ��ϱ�?", "����޼���", MB_YESNOCANCEL);
		}

		case WM_DESTROY:
		{
			PostQuitMessage(0);
		}break;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}

//	�����쿡���� �����Լ� �� ���°� ���� �⺻���� ����.
//	�Լ��� ���ڼ���
//	1. ���μ��� �ڵ�
//	2. ���� ���μ��� �ڵ�
//	3. ����� �μ�( char*[���ڿ�] )
//	4. �⺻â ���� -> �� ���ڸ� ������ ������ â�� ���������� ���ϴ�.
int APIENTRY WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR CmdParam, int CmdShow)
{
	//	1. ������ Ŭ���� �����ϰ� ����ϱ�
	WNDCLASS wndClass = {}; //	������Ŭ����Ÿ���� wndClass ������ �����ϰ� �ʱ�ȭ

	//	1-1. ������ Ŭ������ ���������� ��������ϴ� �κ�
	wndClass.lpszClassName = g_WindowName;	//	���� ������ â�� �̸��� ����
	wndClass.hInstance = hInst;	//	���� �������� �ڵ鰪
	wndClass.lpfnWndProc = WndProc;	//	�ݹ��Լ��� ��� -> �Լ������� �̿�

	wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);	 //	���� ����
	wndClass.hCursor = LoadCursor(nullptr, IDC_ARROW);	//	Ŀ����� ����
	wndClass.hIcon = LoadIcon(nullptr, IDI_APPLICATION);	//	������ ��� ����

	RegisterClass(&wndClass);	//	��������� ������ ������ Ŭ������ ��� -> &(���۷���, ����)�� ���� ����

	//	CreateWindow �Լ��� 3��° ���ڿ� ���� �ɼǸ޴��� �̷������� ������ �������־ ��
	int wsOption = WS_OVERLAPPEDWINDOW;

	//	���� ������ ũ�� ���ϱ� ���� ����ü����
	RECT rt = { 0, 0, WIN_WIDTH, WIN_HEIGHT };

	//	������ ���� ũ��� ����âũ�� ����
	//	���ڼ���
	//	1. ����ü ������ ���۷���
	//	2. ������ �ɼ��� ���� ����
	//	3. ��Ÿ�� �÷���
	AdjustWindowRect(&rt, wsOption, FALSE);

	//	2. ������ ���� �� ȭ�� ����
	HWND hWnd = nullptr;

	//	�������� ������ �����κ���
	//	���ں� ����
	//	1. ���� ������ ������ Ŭ���� �̸�
	//	2. ������ Ÿ��Ʋ(������ ��ܺκп� ǥ�õǴ� ���� ����)
	//	3. ������ �⺻�ɼ�	(ĸ�ǹ�, �ּҹ�ư, �ִ�ȭ��ư)
	//	4. ������â�� ������ ��ġ
	//	5. ������ ������ â�� ũ��
	//	6. �θ��������ڵ�(�ֻ��� ������ �ڵ�)
	//	7. �޴��ڵ�
	//	8. ������ ���μ��� �ڵ�
	//	9. ���� ��(������)
	hWnd = CreateWindow(g_WindowName, "���� ù ��° ������", wsOption, 0, 40, rt.right - rt.left, rt.bottom - rt.top, nullptr, nullptr, hInst, nullptr);

	//	���� �����찡 �������� �ʾҴٸ� �����ϴ� ����ó��
	if (hWnd == nullptr)
	{
		return 0;
	}

	//	������ â ����
	ShowWindow(hWnd, CmdShow);

	//	�޼��� ����ü ���� �����ϰ� �ʱ�ȭ
	MSG msg = {};

	//	� ���·� �޼����� ������ �����ϴ� �κ�
	//	���� ������ �޼����� ���α׷��� ���ư��� ���� ��� ȣ��Ǿ�� �ϱ⶧���� while�� ���ѷ��� ����
	//	���� �⺻���� GetMessage �Լ��� �̿� ���� ���Ӱ������� ���� ���� PeekMessage�� ����ؼ� �� �κп��� ��� �޼���ó���� ��
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		//	�����쿡�� �߻��� �޼����� �а� ������ ���ν���(��ܺκп� �ִ� �ݹ��Լ�)�� �����ϴ� ����
		//	�׷��� �߼۵� �޼������� ���ν������� ó����
		//	������ �޼��� -> ���ν����� ���¸� ��� ���ν������� ó���ǰ� ��ȯ�� �޼������� dispatchmessage �Լ������� ��ȯ��
		//	dispatchmessage �Լ����� �޼��� ������ ���� �޼��� ó���� ���ؼ� �ٽ� GetMessage �Լ��� ȣ��
		//	GetMessage -> DispatchMessage -> WndProc �� ������ ó����
		DispatchMessage(&msg);
	}

	//	�̺κ���...return 0;�̶� ����Ѱǵ�..
	//	wParam ���� �ڵ��̳� ������ �޾Ƶ��� �� ����ϴ� �����ε�.
	//	�޼��� ����ü���� wParam������ �����ϰڴ�..�� �׷� �ǹ�..
	return msg.wParam;
}