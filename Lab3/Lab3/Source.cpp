#include <Windows.h>
#include <tchar.h>
#define _USE_MATH_DEFINES
#include <math.h>
//#include <random>
#include <stdio.h>
#include <stdlib.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

TCHAR WinName[] = _T("MainFrame");

int WINAPI _tWinMain(HINSTANCE This,		 // ���������� �������� ���������� 
	HINSTANCE Prev, 	// � ����������� �������� ������ 0 
	LPTSTR cmd, 		// ��������� ������ 
	int mode) 		// ����� ����������� ����
{
	HWND hWnd;		// ���������� �������� ���� ��������� 
	MSG msg; 		// ��������� ��� �������� ��������� 
	WNDCLASS wc; 	// ����� ����
	// ����������� ������ ���� 
	wc.hInstance = This;
	wc.lpszClassName = WinName; 				// ��� ������ ���� 
	wc.lpfnWndProc = WndProc; 					// ������� ���� 
	wc.style = CS_HREDRAW | CS_VREDRAW; 			// ����� ���� 
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION); 		// ����������� ������ 
	wc.hCursor = LoadCursor(NULL, IDC_ARROW); 		// ����������� ������ 
	wc.lpszMenuName = NULL; 					// ��� ���� 
	wc.cbClsExtra = 0; 						// ��� �������������� ������ ������ 
	wc.cbWndExtra = 0; 						// ��� �������������� ������ ���� 
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1); 	// ���������� ���� ����� ������ 


	// ����������� ������ ����
	if (!RegisterClass(&wc)) return 0;

	// �������� ���� 
	hWnd = CreateWindow(WinName,			// ��� ������ ���� 
		_T("������ Windows-����������"), 		// ��������� ���� 
		WS_OVERLAPPEDWINDOW, 		// ����� ���� 
		CW_USEDEFAULT,				// x 
		CW_USEDEFAULT, 				// y	 ������� ���� 
		CW_USEDEFAULT, 				// width 
		CW_USEDEFAULT, 				// Height 
		HWND_DESKTOP, 				// ���������� ������������� ���� 
		NULL, 						// ��� ���� 
		This, 						// ���������� ���������� 
		NULL); 					// �������������� ���������� ��� 

	ShowWindow(hWnd, mode); 				// �������� ����

	// ���� ��������� ��������� 
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg); 		// ������� ���������� ����� ������� ������� 
		DispatchMessage(&msg); 		// �������� ��������� ������� WndProc() 
	}
	return 0;
}

// ������� ������� ���������� ������������ ��������
// � �������� ��������� �� ������� ��� ������� ����������

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static int x0 = 500, y0 = 300, t;
	int x, y;
	//double a;
	int i, x2, y2,xa,ya;
	double a;
	static double aa = 0;
	int k = 60; //���������� �����
	int  x1, y1, r = 170; // r - ����� ����������
	HDC hdc;
	PAINTSTRUCT ps;
	TCHAR str[32] = { 0 };
	
	static HRGN hRgn;
	static HPEN hpen_black, hpen_red, hpen_blue, hpen_green;
	
	switch (message)		 // ���������� ���������
	{
	case WM_CREATE:
		hpen_black = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
		hpen_red = CreatePen(PS_SOLID, 3, RGB(255, 0, 0));
		hpen_blue = CreatePen(PS_SOLID, 3, RGB(0, 0, 255));
		hpen_green = CreatePen(PS_SOLID, 4, RGB(0, 78, 56));
		break;
	case WM_PAINT:
	{
		//HPEN hPen;
		
		hdc = BeginPaint(hWnd, &ps);
		x = x0;
		y = y0;
		//������
		//std::random_device random_device; // �������� ��������.
		//std::mt19937 generator(random_device()); // ��������� ��������� �����.
		//std::uniform_int_distribution<> distribution(0, 255); // ����������� ������������� [0, 255]
		SelectObject(hdc, hpen_black);

		Ellipse(hdc, 275, 75, 725, 525);

		for (i = 1; i <= k; i++)//���� ��� �����
		{
			a = M_PI * i * 2 / k;
			x1 = x + round(r * cos(a));
			y1 = y + round(r * sin(a));
			MoveToEx(hdc, x, y, NULL);
			LineTo(hdc, x1, y1);
		}

		SelectObject(hdc, hpen_blue);
		for (i = 1; i <= 12; i++)//���� ��� �����
		{
			a = M_PI * i * 2 / 12;
			x1 = x + round((r+10) * cos(a));
			y1 = y + round((r + 10) * sin(a));
			MoveToEx(hdc, x, y, NULL);
			LineTo(hdc, x1, y1);
		}

		SelectObject(hdc, hpen_black);
		
		//int sr, i, x, x1, y2, x2, y2;
		//double a;
		//sr = 120;
		//hPen = CreatePen(PS_SOLID, 3, RGB(255, 0, 0));
		//SelectObject(hdc, hPen);
		//
		//a= M_PI * (x + 45) * 6 / 180;
		//x1= 600 + round(sr * cos(a)); 
		//y1= 400 + round(sr * sin(a));
		//MoveToEx(hdc, 600, 400, NULL);
		//LineTo(hdc, x1, y1);

		////sleep(1000);

		//sr= 120;
		//setpencolor(clwhite);
		//a= pi * (x + 45) * 6 / 180;
		//x1= 600 + round(sr * cos(a)); 
		//y1= 400 + round(sr * sin(a));
		//line(600, 400, x1, y1);


		//setpencolor(clblack);
		//a= pi * (x + 45) * 6 / 180;
		//x1= 600 + round(r * cos(a)); 
		//y1= 400 + round(r * sin(a));
		//line(600, 400, x1, y1);


		//setpencolor(clblack); 
		//circle(600, 400, 80);

		Ellipse(hdc, 350, 150, 650, 450);
		//circle(600, 400, 135); 
		//char p[17];
		for (i = 0; i <= 11; i++)
		{
		a= M_PI * (i + 10) * 30 / 180;
		x2= 500 + round((r + 30) * cos(a));
		y2= 290 + round((r + 30) * sin(a));
		if (i > 9) x2= x2 - 3;
		_itow_s(5*(i+1), str, 10);
		//TextOutA(hdc, x2, y2, "5", strlen("5"));
		TextOut(hdc, x2, y2, str, _tcsclen(str));
		}


		SelectObject(hdc, hpen_green);
		//if (t%60==0) 
			aa = M_PI * (t - 900) * 2 / (k * 60);
		xa = x + round((r - 50) * cos(aa));
		ya = y + round((r - 50) * sin(aa));

		MoveToEx(hdc, x, y, NULL);
		LineTo(hdc, xa, ya);

		SelectObject(hdc, hpen_red);
		a = M_PI * (t-15) * 2 / k;
		x1 = x + round(r * cos(a));
		y1 = y + round(r * sin(a));
		MoveToEx(hdc, x, y, NULL);
		LineTo(hdc, x1, y1);


		_itow_s(t, str, 10);
		TextOut(hdc, 100, 100, str, _tcsclen(str));
		EndPaint(hWnd, &ps);
	}
	break;

	case WM_LBUTTONDOWN:
		SetTimer(hWnd, 1, 1000, NULL);
		break;
	case WM_RBUTTONDOWN:
		t = 0;
		InvalidateRect(hWnd, NULL, TRUE);
		break;
	case WM_TIMER:
		t++;
		//if (t == 60) t = 0;
		InvalidateRect(hWnd, NULL, TRUE);
		break;
	/*case WM_SIZE:
		sx = LOWORD(lParam);
		sy = HIWORD(lParam);
		break;*/
	case WM_CHAR:
		KillTimer(hWnd, 1);
		break;

	case WM_DESTROY:
		KillTimer(hWnd, 1);
		DeleteObject(hpen_black);
		DeleteObject(hpen_red);
		DeleteObject(hpen_blue);
		DeleteObject(hpen_green);
		PostQuitMessage(0);
		break; 			// ���������� ��������� 
	default: 			// ��������� ��������� �� ��������� 
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}












