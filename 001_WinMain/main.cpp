#undef UNICODE	//	유니코드 문자열을 사용하지 않겠다는 의미
#include <Windows.h>	//	윈도우 프로그래밍에서 가장 중요한 헤더파일..이거 없으면 아무고토 모탐..

//	현재 윈도우 창의 크기 설정 (이게 좀 더 편하드라구여..ㅎㅎ)
#define WIN_WIDTH 800
#define WIN_HEIGHT 600

//	현재 윈도우 프로그램의 이름을 지정하는 부분
LPCSTR g_WindowName = "기본윈도우창";

//	콜백함수(Call back Function) : 윈도우 운영체제가 대신 호출해주는 함수
//	인자설명
//	1. HWND		: 현재 윈도우의 핸들값, 핸들에 대해서는 추후 설명
//	2. UINT		: 현재 윈도우에서 발생된 메세지를 담을 변수
//	3. WPARAM	: 메시지를 수식하는 WORD형 매개변수, 핸들 or 정수가 전달됨
//	4. LPARAM	: 메시지를 수식하는 LONG형 매개변수, 포인터가 전달
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	//	윈도우 운영체제는 메세지를 주고받는 형식으로 돌아가는 운영체제.
	//	이 곳에 윈도우에서 처리할 수 있는 모든 종류의 메세지처리가 가능
	//	현재는 윈도우 파괴(close) 부분만 처리해놓은 상태
	switch (msg)
	{
		//	특정 키를 눌렀을 때 발생하는 메세지
		case WM_KEYDOWN:
		{
			switch (wParam)
			{
				//	ESC키를 눌렀을 때 발생하는 메세지 / 종료버튼
			case VK_ESCAPE:
				PostQuitMessage(0);
				break;

			default:
				break;
			}
		}

		//	오른쪽 마우스버튼을 눌렀을 때 발생하는 메세지 / 메세지박스
		case WM_RBUTTONDOWN:
		{
			MessageBox(hWnd, "정말 종료하시겠습니까?", "종료메세지", MB_YESNOCANCEL);
		}

		case WM_DESTROY:
		{
			PostQuitMessage(0);
		}break;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}

//	윈도우에서의 메인함수 이 형태가 가장 기본적인 형태.
//	함수의 인자설명
//	1. 프로세스 핸들
//	2. 이전 프로세스 핸들
//	3. 명령줄 인수( char*[문자열] )
//	4. 기본창 상태 -> 이 인자를 가지고 윈도우 창을 직접적으로 띄웁니다.
int APIENTRY WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR CmdParam, int CmdShow)
{
	//	1. 윈도우 클래스 정의하고 등록하기
	WNDCLASS wndClass = {}; //	윈도우클래스타입의 wndClass 변수를 선언하고 초기화

	//	1-1. 윈도우 클래스의 직접적으로 정보등록하는 부분
	wndClass.lpszClassName = g_WindowName;	//	현재 윈도우 창의 이름을 정의
	wndClass.hInstance = hInst;	//	현재 윈도우의 핸들값
	wndClass.lpfnWndProc = WndProc;	//	콜백함수를 등록 -> 함수포인터 이용

	wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);	 //	배경색 설정
	wndClass.hCursor = LoadCursor(nullptr, IDC_ARROW);	//	커서모양 선택
	wndClass.hIcon = LoadIcon(nullptr, IDI_APPLICATION);	//	아이콘 모양 선택

	RegisterClass(&wndClass);	//	방금전까지 설정한 윈도우 클래스를 등록 -> &(레퍼런스, 참조)는 추후 설명

	//	CreateWindow 함수에 3번째 인자에 들어가는 옵션메뉴를 이런식으로 변수로 지정해주어도 됨
	int wsOption = WS_OVERLAPPEDWINDOW;

	//	실제 윈도우 크기 구하기 위한 구조체변수
	RECT rt = { 0, 0, WIN_WIDTH, WIN_HEIGHT };

	//	위에서 구한 크기로 실제창크기 지정
	//	인자설명
	//	1. 구조체 변수의 레퍼런스
	//	2. 윈도우 옵션을 담은 변수
	//	3. 불타입 플레그
	AdjustWindowRect(&rt, wsOption, FALSE);

	//	2. 윈도우 생성 및 화면 띄우기
	HWND hWnd = nullptr;

	//	직접적인 윈도우 생성부분임
	//	인자별 설명
	//	1. 위에 설정한 윈도우 클래스 이름
	//	2. 윈도우 타이틀(윈도우 상단부분에 표시되는 제목 설정)
	//	3. 윈도우 기본옵션	(캡션바, 최소버튼, 최대화버튼)
	//	4. 윈도우창이 생성될 위치
	//	5. 생성될 윈도우 창의 크기
	//	6. 부모윈도우핸들(최상위 윈도우 핸들)
	//	7. 메뉴핸들
	//	8. 연결할 프로세스 핸들
	//	9. 몰라도 됨(무쓸모)
	hWnd = CreateWindow(g_WindowName, "나의 첫 번째 윈도우", wsOption, 0, 40, rt.right - rt.left, rt.bottom - rt.top, nullptr, nullptr, hInst, nullptr);

	//	만약 윈도우가 생성되지 않았다면 종료하는 예외처리
	if (hWnd == nullptr)
	{
		return 0;
	}

	//	윈도우 창 띄우기
	ShowWindow(hWnd, CmdShow);

	//	메세지 구조체 변수 생성하고 초기화
	MSG msg = {};

	//	어떤 형태로 메세지를 돌릴지 선택하는 부분
	//	보통 윈도우 메세지는 프로그램이 돌아가는 동안 계속 호출되어야 하기때문에 while로 무한루프 돌림
	//	가장 기본적인 GetMessage 함수를 이용 추후 게임같은것을 만들 때는 PeekMessage를 사용해서 그 부분에서 모든 메세지처리를 함
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		//	윈도우에서 발생한 메세지를 읽고 윈도우 프로시져(상단부분에 있는 콜백함수)로 전달하는 역할
		//	그렇게 발송된 메세지들이 프로시져에서 처리됨
		//	생성된 메세지 -> 프로시져의 형태를 띄며 프로시져에서 처리되고 반환된 메세지들은 dispatchmessage 함수에서도 반환됨
		//	dispatchmessage 함수에서 메세지 루프는 다음 메세지 처리를 위해서 다시 GetMessage 함수를 호출
		//	GetMessage -> DispatchMessage -> WndProc 의 구조로 처리됨
		DispatchMessage(&msg);
	}

	//	이부분은...return 0;이랑 비슷한건데..
	//	wParam 값이 핸들이나 정수를 받아들일 때 사용하는 인자인데.
	//	메세지 구조체에서 wParam값으로 리턴하겠다..뭐 그런 의미..
	return msg.wParam;
}