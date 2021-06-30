// Sinusoid.cpp: ���������� ����� ����� ��� ����������.
//

#include "stdafx.h"
#include "Sinusoid.h"
#include <cmath>


#define MAX_LOADSTRING 100

// ���������� ����������:
HINSTANCE hInst;                                // ������� ���������
WCHAR szTitle[MAX_LOADSTRING];                  // ����� ������ ���������
WCHAR szWindowClass[MAX_LOADSTRING];            // ��� ������ �������� ����
int x = 1000;
int y = 500;
int v = 1, b = 1;
wchar_t *v1,*b1;
double i = -10;
BOOL key;
// ��������� ���������� �������, ���������� � ���� ������ ����:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: ���������� ��� �����.

    // ������������� ���������� �����
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_SINUSOID, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // ��������� ������������� ����������:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_SINUSOID));

    MSG msg;

    // ���� ��������� ���������:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  �������: MyRegisterClass()
//
//  ����������: ������������ ����� ����.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_SINUSOID));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_SINUSOID);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}
HWND hEdt;
HWND hBtn1;
HWND hBtn;
HWND hEdt2;

//
//   �������: InitInstance(HINSTANCE, int)
//
//   ����������: ��������� ��������� ���������� � ������� ������� ����.
//
//   �����������:
//
//        � ������ ������� ���������� ���������� ����������� � ���������� ����������, � �����
//        ��������� � ��������� �� ����� ������� ���� ���������.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // ��������� ���������� ���������� � ���������� ����������

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }
   hBtn = CreateWindow(L"BUTTON", L"���������", BS_PUSHBUTTON | WS_VISIBLE | WS_CHILD | WS_TABSTOP, 800, 45, 200, 30, hWnd, (HMENU)1, HINSTANCE(hInst), NULL);
   hBtn1 = CreateWindow(L"BUTTON", L"��������", BS_PUSHBUTTON | WS_VISIBLE | WS_CHILD | WS_TABSTOP, 800, 80, 200, 30, hWnd, (HMENU)2, HINSTANCE(hInst), NULL);
   hEdt = CreateWindow(L"EDIT", L"", WS_VISIBLE | WS_CHILD | WS_TABSTOP | WS_BORDER, 550, 45, 200, 30, hWnd, NULL, HINSTANCE(hInst), NULL);
   hEdt2 = CreateWindow(L"EDIT", L"", WS_VISIBLE | WS_CHILD | WS_TABSTOP | WS_BORDER, 550, 80, 200, 30, hWnd, NULL, HINSTANCE(hInst), NULL);

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);


   return TRUE;
}

//
//  �������: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  ����������:  ������������ ��������� � ������� ����.
//
//  WM_COMMAND � ���������� ���� ����������
//  WM_PAINT � ���������� ������� ����
//  WM_DESTROY � ��������� ��������� � ������ � ���������
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		// ��������� ����� � ����:
		switch (wmId)
		{
		case 1:
		{
			if ((GetWindowTextLength(hEdt) == 0) || (GetWindowTextLength(hEdt2) == 0))
			{
				MessageBox(NULL, L"��������� ������", L"������", MB_OK);
				return 0;
			}
			v1 = new wchar_t[10];
			b1 = new wchar_t[10];
			GetWindowText(hEdt, v1, 10);
			GetWindowText(hEdt2, b1, 10);
			v = _wtoi(v1);
			b = _wtoi(b1);
			if ((v < 1) || (b < 1))
			{
				MessageBox(NULL, L"������� ���������� ��������", L"������", MB_OK);
				return 0;
			}
			key = true;
			delete[] v1;
			delete[] b1;
			InvalidateRect(hWnd, 0, 1);
			break;
		}
		case 2:
		{
			v = 1;
			b = 1;
			SetWindowText(hEdt2, L"");
			SetWindowText(hEdt, L"");
			InvalidateRect(hWnd, 0, 1);
		}
		}
		break;
	}
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: �������� ���� ����� ��� ����������, ������������ HDC...
			TextOut(hdc, 480, 50, L"�������", 12);
			TextOut(hdc, 460, 90, L"���������", 12);
			MoveToEx(hdc, 800, 400, NULL);
			LineTo(hdc, 0, 400);
			MoveToEx(hdc, 400, 0, NULL);
			LineTo(hdc, 400, 800);

			MoveToEx(hdc, 400, 0, NULL);
			LineTo(hdc, 390, 10);
			MoveToEx(hdc, 410, 10, NULL);
			LineTo(hdc, 400, 0);
			TextOut(hdc, 415, 0, L"Y", 1);
			MoveToEx(hdc, 790, 390, NULL);
			LineTo(hdc, 800, 400);
			LineTo(hdc, 790, 410);
			TextOut(hdc, 800, 415, L"X", 1);
			TextOut(hdc, 410, 410, L"0", 1);
			if (b > 14)
				b = 14;
			MoveToEx(hdc, i * 20 + 200, sin(i)*(-20) + 200, NULL);
			for (i = -10; i <= 10; i = i + (0.01/(v*b)))
			{
				//LineTo(hdc,i*20+200,sin(i)*(-20)+200);
				SetPixel(hdc, i * (20*v) + 400, b*sin(i)*(-20) + 400, RGB(255, 0, 0));
			}
            EndPaint(hWnd, &ps);
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

// ���������� ��������� ��� ���� "� ���������".