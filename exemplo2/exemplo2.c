#include <windows.h>

int WINAPI WinMain(HINSTANCE hThisInst, HINSTANCE hPrevInst, LPSTR lpszCmdLine, int nWinMode) {

	MessageBoxEx(NULL, lpszCmdLine, "Hello World", MB_OK | MB_ICONINFORMATION | MB_TASKMODAL, 0);

	return 0;

}
