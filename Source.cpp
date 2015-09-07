#include <windows.h>

TCHAR szClassName[] = TEXT("window");

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_CREATE:
		CreateWindow(TEXT("BUTTON"), TEXT("PrintScreen"), WS_VISIBLE | WS_CHILD, 10, 10, 256, 32, hWnd, (HMENU)100, ((LPCREATESTRUCT)lParam)->hInstance, 0);
		CreateWindow(TEXT("BUTTON"), TEXT("Alt + PrintScreen"), WS_VISIBLE | WS_CHILD, 10, 50, 256, 32, hWnd, (HMENU)101, ((LPCREATESTRUCT)lParam)->hInstance, 0);
		break;
	case WM_COMMAND:
		if (LOWORD(wParam) == 100)
		{
			keybd_event(VK_SNAPSHOT, 0, 0, 0);
			keybd_event(VK_SNAPSHOT, 0, KEYEVENTF_KEYUP, 0);
		}
		else if (LOWORD(wParam) == 101)
		{
			keybd_event(VK_MENU, 0, 0, 0);
			keybd_event(VK_SNAPSHOT, 0, 0, 0);
			keybd_event(VK_SNAPSHOT, 0, KEYEVENTF_KEYUP, 0);
			keybd_event(VK_MENU, 0, KEYEVENTF_KEYUP, 0);
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}
	return 0;
}

int WINAPI WinMain(HINSTANCE hinst, HINSTANCE hPreInst,
	LPSTR pCmdLine, int nCmdShow)
{
	HWND hWnd;
	MSG msg;
	WNDCLASS wndclass;
	if (!hPreInst)
	{
		wndclass.style = CS_HREDRAW | CS_VREDRAW;
		wndclass.lpfnWndProc = WndProc;
		wndclass.cbClsExtra = 0;
		wndclass.cbWndExtra = 0;
		wndclass.hInstance = hinst;
		wndclass.hIcon = NULL;
		wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
		wndclass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
		wndclass.lpszMenuName = NULL;
		wndclass.lpszClassName = szClassName;
		if (!RegisterClass(&wndclass))
			return FALSE;
	}
	hWnd = CreateWindowEx(
		WS_EX_NOACTIVATE,
		szClassName,
		TEXT("Print Screen"),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		0,
		CW_USEDEFAULT,
		0,
		0,
		0,
		hinst,
		0);
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}