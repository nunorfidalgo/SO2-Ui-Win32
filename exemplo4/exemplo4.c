#include <windows.h>
#include <tchar.h>

typedef struct {
	int xi, yi, xf, yf;
} Rect;

#define MAX_RECTS 250

Rect mat[MAX_RECTS];
int numrect;
int drawing;

int x1, y1, x2, y2;
POINT p;

ATOM RegistaClasse(HINSTANCE hThisInst, TCHAR *szWinName);
HWND CriarJanela(HINSTANCE hThisInst, TCHAR *szWinName);
LRESULT CALLBACK WindowFunc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

int WINAPI _tWinMain(HINSTANCE hThisInst, HINSTANCE hPrevInst, LPSTR lpszCmdLine, int nWinMode) {

#ifdef _UNICODE
#define _tWinMain wWinMain
#else
#define _tWinMain WinMain
#endif

	TCHAR JanelaPrinc[] = TEXT("Rects");
	HWND hwnd;
	MSG msg;

	//MessageBoxEx(NULL, lpszCmdLine, TEXT("Hello World"), MB_OK | MB_ICONINFORMATION | MB_TASKMODAL, 0);
	MessageBoxEx(NULL, TEXT("TESTE"), TEXT("Hello World"), MB_OK | MB_ICONINFORMATION | MB_TASKMODAL, 0);
	

	if (!RegistaClasse(hThisInst, JanelaPrinc))
		return 0;

	hwnd = CriarJanela(hThisInst, JanelaPrinc);

	ShowWindow(hwnd, nWinMode);
	UpdateWindow(hwnd);

	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;

}

ATOM RegistaClasse(HINSTANCE hThisInst, TCHAR *szWinName) {
	WNDCLASSEX wcl;

	wcl.cbSize = sizeof(WNDCLASSEX);
	wcl.hInstance = hThisInst;
	wcl.lpszClassName = szWinName;
	wcl.lpfnWndProc = WindowFunc;
	wcl.style = CS_HREDRAW; //CS_GLOBALCLASS
	wcl.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wcl.hIconSm = LoadIcon(NULL, IDI_WINLOGO);
	//wcl.hIconSm = LoadIcon(hThisInst, (LPCTSTR)IDI_ICON1);
	wcl.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcl.lpszMenuName = NULL;
	wcl.cbClsExtra = 0;
	wcl.cbWndExtra = 0;
	wcl.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);

	return RegisterClassEx(&wcl);
}

HWND CriarJanela(HINSTANCE hThisInst, TCHAR *szWinName) {
	return CreateWindow(
		szWinName,
		TEXT("SO2 - exemplo Win32"),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		HWND_DESKTOP,
		NULL,
		hThisInst,
		NULL
	);
}

LRESULT CALLBACK WindowFunc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
	static TCHAR *msg = TEXT("Desenho de Rectângulos");
	PAINTSTRUCT ps;
	HDC hdc;
	int i;
	switch (message) {
	case WM_CREATE:
		drawing = 0;
		numrect = 0;
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_LBUTTONDOWN:
		x1 = LOWORD(lParam);
		y1 = HIWORD(lParam);
		drawing = 1;
	case WM_MOUSEMOVE:
		if (drawing == 1) {
			x2 = LOWORD(lParam);
			y2 = HIWORD(lParam);
			InvalidateRect(hwnd, NULL, TRUE);
		}
		break;
	case WM_LBUTTONUP:
		if (drawing == 1) {
			x2 = LOWORD(lParam);
			y2 = HIWORD(lParam);
			mat[numrect].xi = x1;
			mat[numrect].yi = y1;
			mat[numrect].xf = x2;
			mat[numrect].yf = y2;
			if (numrect < MAX_RECTS - 1)
				numrect++;
			drawing = 0;
			InvalidateRect(hwnd, NULL, TRUE);
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		TextOut(hdc, 50, 50, msg, _tcslen(msg));
		for (i = 0; i < numrect; i++) {
			Rectangle(hdc, mat[i].xi, mat[i].yi, mat[i].xf, mat[i].yf);
		}
		if (drawing == 1) {
			Rectangle(hdc, x1, y1, x2, y2);
		}
		EndPaint(hwnd, &ps);
		break;
	default:
		return DefWindowProc(hwnd, message, wParam, lParam);
	}
	return 0;
}