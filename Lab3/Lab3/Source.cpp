#include <Windows.h>
#include <tchar.h>
#define _USE_MATH_DEFINES
#include <math.h>
//#include <random>
#include <stdio.h>
#include <stdlib.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

TCHAR WinName[] = _T("MainFrame");

int WINAPI _tWinMain(HINSTANCE This,		 // Дескриптор текущего приложения 
	HINSTANCE Prev, 	// В современных системах всегда 0 
	LPTSTR cmd, 		// Командная строка 
	int mode) 		// Режим отображения окна
{
	HWND hWnd;		// Дескриптор главного окна программы 
	MSG msg; 		// Структура для хранения сообщения 
	WNDCLASS wc; 	// Класс окна
	// Определение класса окна 
	wc.hInstance = This;
	wc.lpszClassName = WinName; 				// Имя класса окна 
	wc.lpfnWndProc = WndProc; 					// Функция окна 
	wc.style = CS_HREDRAW | CS_VREDRAW; 			// Стиль окна 
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION); 		// Стандартная иконка 
	wc.hCursor = LoadCursor(NULL, IDC_ARROW); 		// Стандартный курсор 
	wc.lpszMenuName = NULL; 					// Нет меню 
	wc.cbClsExtra = 0; 						// Нет дополнительных данных класса 
	wc.cbWndExtra = 0; 						// Нет дополнительных данных окна 
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1); 	// Заполнение окна белым цветом 


	// Регистрация класса окна
	if (!RegisterClass(&wc)) return 0;

	// Создание окна 
	hWnd = CreateWindow(WinName,			// Имя класса окна 
		_T("Каркас Windows-приложения"), 		// Заголовок окна 
		WS_OVERLAPPEDWINDOW, 		// Стиль окна 
		CW_USEDEFAULT,				// x 
		CW_USEDEFAULT, 				// y	 Размеры окна 
		CW_USEDEFAULT, 				// width 
		CW_USEDEFAULT, 				// Height 
		HWND_DESKTOP, 				// Дескриптор родительского окна 
		NULL, 						// Нет меню 
		This, 						// Дескриптор приложения 
		NULL); 					// Дополнительной информации нет 

	ShowWindow(hWnd, mode); 				// Показать окно

	// Цикл обработки сообщений 
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg); 		// Функция трансляции кодов нажатой клавиши 
		DispatchMessage(&msg); 		// Посылает сообщение функции WndProc() 
	}
	return 0;
}

// Оконная функция вызывается операционной системой
// и получает сообщения из очереди для данного приложения

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static int x0 = 500, y0 = 300, t;
	int x, y;
	//double a;
	int i, x2, y2,xa,ya;
	double a;
	static double aa = 0;
	int k = 60; //количество лучей
	int  x1, y1, r = 170; // r - длина прорисовки
	HDC hdc;
	PAINTSTRUCT ps;
	TCHAR str[32] = { 0 };
	
	static HRGN hRgn;
	static HPEN hpen_black, hpen_red, hpen_blue, hpen_green;
	
	switch (message)		 // Обработчик сообщений
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
		//рандом
		//std::random_device random_device; // Источник энтропии.
		//std::mt19937 generator(random_device()); // Генератор случайных чисел.
		//std::uniform_int_distribution<> distribution(0, 255); // Равномерное распределение [0, 255]
		SelectObject(hdc, hpen_black);

		Ellipse(hdc, 275, 75, 725, 525);

		for (i = 1; i <= k; i++)//цикл для линий
		{
			a = M_PI * i * 2 / k;
			x1 = x + round(r * cos(a));
			y1 = y + round(r * sin(a));
			MoveToEx(hdc, x, y, NULL);
			LineTo(hdc, x1, y1);
		}

		SelectObject(hdc, hpen_blue);
		for (i = 1; i <= 12; i++)//цикл для линий
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
		break; 			// Завершение программы 
	default: 			// Обработка сообщения по умолчанию 
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}












