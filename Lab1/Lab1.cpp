#include <Windows.h>
#include <tchar.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <random>

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
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 25); 	// Заполнение окна белым цветом 


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
	static int x0 = 50, y0 = 50;
	int x, y;
	double a;
	int k = 30; //количество лучей
	int i, x1, y1, r = 900; // r - длина прорисовки
	HDC hdc;
	PAINTSTRUCT ps;
	static HRGN hRgn;
	switch (message)		 // Обработчик сообщений
	{
	case WM_PAINT:
	{
		HPEN hPen;
		hdc = BeginPaint(hWnd, &ps);
		x = x0;
		y = y0;
		//рандом
		std::random_device random_device; // Источник энтропии.
		std::mt19937 generator(random_device()); // Генератор случайных чисел.
		std::uniform_int_distribution<> distribution(0, 255); // Равномерное распределение [0, 255]

		for (i = 1; i <= k; i++)//цикл для линий
		{
			hPen = CreatePen(PS_SOLID, 3, RGB(distribution(generator), distribution(generator), distribution(generator)));
			SelectObject(hdc, hPen);
			a = M_PI * i * 2 / k;
			x1 = x + (r * cos(a));
			y1 = y + (r * sin(a));
			MoveToEx(hdc, x, y, NULL);
			LineTo(hdc, x1, y1);
		}
		EndPaint(hWnd, &ps);
	}
	break;

	case WM_RBUTTONDOWN:
	{
		hdc = BeginPaint(hWnd, &ps);
		//HDC hdc = GetDC(hWnd);
		x0 = LOWORD(lParam); //узнаём координаты
		y0 = HIWORD(lParam);

		MoveToEx(hdc, 0, 0, NULL);
		LineTo(hdc, x0, y0);

	}
	break;

	case WM_LBUTTONDOWN:
	{
		InvalidateRgn(hWnd, hRgn, true);
	}
	break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break; 			// Завершение программы 
	default: 			// Обработка сообщения по умолчанию 
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
