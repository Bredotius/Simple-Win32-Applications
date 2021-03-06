// KrestikNolik.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "KrestikNolik.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name
int x = 50, y = 50, p = 0, z=0, k=0, v, b, l=1,m,n,c[3][3],d=0;

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY _tWinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPTSTR    lpCmdLine,
	int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_KRESTIKNOLIK, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_KRESTIKNOLIK));

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int)msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
//  COMMENTS:
//
//    This function and its usage are only necessary if you want this code
//    to be compatible with Win32 systems prior to the 'RegisterClassEx'
//    function that was added to Windows 95. It is important to call this function
//    so that the application will get 'well formed' small icons associated
//    with it.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_KRESTIKNOLIK));
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{

	hInst = hInstance; // Store instance handle in our global variable

	HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU,
		0, 0, 265, 300, nullptr, nullptr, hInstance, nullptr);
	HMENU hMenu = CreateMenu();
	AppendMenu(hMenu, MF_STRING, 1000, L"Новая игра");
	AppendMenu(hMenu, MF_STRING, 1010, L"Выход");
	SetMenu(hWnd, hMenu);

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;

	switch (message)
	{
	case WM_COMMAND:
	{
		wmId = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case 1000:
		{
			l = 0;
			d = 0;
			k = 0;
			z = 0;
			for (n = 0; n<3; n++)
				for (m = 0; m<3; m++)
					c[n][m] = 0;
			InvalidateRect(hWnd, 0, 1);
			UpdateWindow(hWnd);
			l = 1;
			break;
		}
		case 1010:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	}
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
			for (; k < 3; y = y + 50)
			{
				for (; z < 3; x = x + 50)
				{
					Rectangle(hdc, x, y, x + 50, y + 50);
					z = z + 1;
				}
				z = 0;
				x = 50;
				Rectangle(hdc, x, y, x + 50, y + 50);
				k = k + 1;
			}
		x = 50;
		y = 50;
			if (p > 0 && l == 1 && c[n][m]==0)
			{

				MoveToEx(hdc, v, b, NULL);
				LineTo(hdc, v+50,  b+50);
				MoveToEx(hdc, v, b+50, NULL);
				LineTo(hdc, v+50, b);
				c[n][m] = 1;
				d++;
				l = 2;
			}
			else if (p > 0 && l == 2 && c[n][m] == 0)
			{
				Ellipse(hdc, v, b, v + 50, b + 50);
				c[n][m] = 2;
				l = 1;
				d++;
			}
			if (c[0][0] == 2 && c[0][1] == 2 && c[0][2] == 2 || c[1][0] == 2 && c[1][1] == 2 && c[1][2] == 2 || c[2][0] == 2 && c[2][1] == 2 && c[2][2] == 2 ||
				c[0][0] == 2 && c[1][0] == 2 && c[2][0] == 2 || c[0][1] == 2 && c[1][1] == 2 && c[2][1] == 2 || c[0][2] == 2 && c[1][2] == 2 && c[2][2] == 2 ||
				c[0][0] == 2 && c[1][1] == 2 && c[2][2] == 2 || c[0][2] == 2 && c[1][1] == 2 && c[2][0] == 2)
			{
				MessageBox(hWnd, L"Нолики выиграли", L"Конец игры", MB_OK | MB_ICONQUESTION);
			}

		if (c[0][0] == 1 && c[0][1] == 1 && c[0][2] == 1 || c[1][0] == 1 && c[1][1] == 1 && c[1][2] == 1 || c[2][0] == 1 && c[2][1] == 1 && c[2][2] == 1 ||
				c[0][0] == 1 && c[1][0] == 1 && c[2][0] == 1 || c[0][1] == 1 && c[1][1] == 1 && c[2][1] == 1 || c[0][2] == 1 && c[1][2] == 1 && c[2][2] == 1 ||
				c[0][0] == 1 && c[1][1] == 1 && c[2][2] == 1 || c[0][2] == 1 && c[1][1] == 1 && c[2][0] == 1)
				MessageBox(hWnd, L"Крестики выиграли", L"Конец игры", MB_OK | MB_ICONQUESTION);
		if(d==9)
			MessageBox(hWnd, L"Начните новую игру", L"Конец игры", MB_OK | MB_ICONQUESTION);
		EndPaint(hWnd, &ps);
		break;
	}
	break;
	case WM_LBUTTONDOWN:
	{
		int x1 = LOWORD(lParam);
		int y1 = HIWORD(lParam);
		for (; y<151; y = y + 50)
		{
			for (; x<151; x = x + 50)
			{
				if ((x1>x) && (x1<x + 50) && (y1>y) && (y1<y + 50))
				{
					v = x;
					b = y;
					m = (y / 50) - 1;
					n = (x / 50) - 1;
					p = p + 1;
					InvalidateRect(hWnd, 0, 0);
				}
			}
			x = 50;
		}
		y = 50;
	}
	break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}