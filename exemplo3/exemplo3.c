#include <windows.h>

int WINAPI WinMain(HINSTANCE hThisInst, HINSTANCE hPrevInst, LPSTR lpszCmdLine, int nWinMode) {

	MessageBoxEx(NULL, __argv[0], "Command Line[0]", MB_OK | MB_ICONINFORMATION | MB_TASKMODAL, 0);

	return 1;
}