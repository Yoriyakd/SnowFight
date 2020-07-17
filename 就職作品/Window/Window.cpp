#include"window.h"

const HWND& Window::GetHWND(void)
{
	return hwnd;
}

const bool Window::IsFullScreen(void)
{
	return isFullScreen;
}

bool Window::InitWindow(const HINSTANCE& _hInst, const int _nCmdshow)
{
	WNDCLASS wc;
	char szAppName[] = "Generic Game SDK Window";

	wc.style = CS_DBLCLKS;
	wc.lpfnWndProc = WndFunc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = _hInst;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = szAppName;

	RegisterClass(&wc);

	hwnd = CreateWindowEx(
		0,
		szAppName,
		"SnowBallFight Ver.0.9.4",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		SCRW, SCRH,
		NULL, NULL, _hInst,
		NULL);

	if (!hwnd)return FALSE;

	ShowWindow(hwnd, _nCmdshow);
	UpdateWindow(hwnd);
	SetFocus(hwnd);

	isFullScreen = false;	// ウィンドウモード
	if (MessageBox(NULL, "フルスクリーンで起動しますか?", "起動確認", MB_YESNO | MB_DEFBUTTON2 | MB_ICONQUESTION) == IDYES)
	{
		isFullScreen = true;
	}

	else {
		RECT rc = { 0,0,SCRW,SCRH };
		AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);
		SetWindowPos(hwnd, NULL, 50, 50, rc.right - rc.left, rc.bottom - rc.top, SWP_SHOWWINDOW | SWP_NOZORDER);


		if (hwnd != nullptr)
		{
			return true;
		}

	}
		return true;
}


LRESULT APIENTRY Window::WndFunc(HWND _hwnd, UINT _msg, WPARAM _wParam, LPARAM _lParam)
{
	switch (_msg) {
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

	}
	return DefWindowProc(_hwnd, _msg, _wParam, _lParam);

}

Window::Window(void)
{
}

Window::~Window(void)
{
}
