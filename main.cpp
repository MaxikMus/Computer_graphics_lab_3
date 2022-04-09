#include "hex.h"

#define _WIN32_WINNT 0x0A00

// const 
// xmax
// ymax

const long maxX = 1000;
const long maxY = 550;

LRESULT APIENTRY WndProc(_In_ HWND hWnd, _In_ UINT Msg, _In_ WPARAM wParam, _In_ LPARAM lParam);
void control(unsigned int key);
void showWin(PAINTSTRUCT ps, HDC hdc);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow) {

	WNDCLASSEXW wcex;
	memset(&wcex, 0, sizeof(WNDCLASSEX));
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.lpszClassName = L"My class";
	wcex.lpfnWndProc = WndProc;
	RegisterClassExW(&wcex);

	HWND hwnd = CreateWindowW(L"My class", L"Second Lab", WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME & ~WS_MAXIMIZEBOX,
		0, 0, maxX, maxY, NULL, NULL, NULL, NULL);

	ShowWindow(hwnd, SW_SHOWNORMAL);


	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}


	return (int)msg.wParam;
}

HEX obj;

LRESULT APIENTRY WndProc(_In_ HWND hWnd, _In_ UINT Msg, _In_ WPARAM wParam, _In_ LPARAM lParam) {
	unsigned int key;
	switch (Msg)
	{
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);

		showWin(ps, hdc);


		EndPaint(hWnd, &ps);
	}
	break;
	case WM_KEYDOWN:
		key = (int)wParam;
		control(key);
		InvalidateRect(hWnd, NULL, true);
		UpdateWindow(hWnd);

		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, Msg, wParam, lParam);
	}
	return 0;
}

void showWin(PAINTSTRUCT ps, HDC hdc) {
	// TODO: Добавьте сюда любой код прорисовки, использующий HDC...
	HDC memDC = CreateCompatibleDC(hdc);
	HBITMAP memBM = CreateCompatibleBitmap(hdc, ps.rcPaint.right - ps.rcPaint.left, ps.rcPaint.bottom - ps.rcPaint.top);

	SelectObject(memDC, memBM);
	//отрисовка:
	// 
	//Заполнение буфера белым цветом
	FillRect(memDC, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));

	obj.showHex(memDC);
	//shade(obj.getPoint(), memDC, maxX, maxY);





	//Загрузка буфера в битмап графического устройства и освобождение памяти выделенной на буфер
	BitBlt(hdc, 0, 0, ps.rcPaint.right - ps.rcPaint.left, ps.rcPaint.bottom - ps.rcPaint.top, memDC, 0, 0, SRCCOPY);
	DeleteDC(memDC);
	DeleteObject(memBM);
}

float speed = 10.0f;
void control(unsigned int key) {

	switch (key)
	{
	case 'q':
	case 'Q':
		obj.rotate(gradToRad(5));
		break;
	case 'e':
	case 'E':
		obj.rotate(gradToRad(-5));
		break;
		// движение по осям X и Y
	case 'w':
	case 'W':
		obj.move(1, -speed);
		break;
	case 's':
	case 'S':
		obj.move(1, speed);
		break;
	case 'a':
	case 'A':
		obj.move(0, -speed);
		break;
	case 'd':
	case 'D':
		obj.move(0, speed);
		break;
		// масштабирование		
		// увеличение
	case 'r':
	case 'R':
		obj.scale(1.1f);
		break;
		// уменьшение
	case 'f':
	case 'F':
		obj.scale(0.9f);
		break;
	default:
		break;
	}
}