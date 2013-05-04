#include <windows.h>
#include "WindowProc.h"
#include "Constants.h"

/*  This function is called by the Windows function DispatchMessage()  */

LRESULT CALLBACK WindowProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    static HWND      pluginWindow = 0; // We will fill it forever in the processing of the WM_CREATE message
    static HINSTANCE hDLL         = LoadLibrary(menoDLL);
    int    sirka;
    int    dlzka;

    typedef HWND  (__cdecl * LISTLOADFUNC)                 (HWND ParentWin, char* FileToLoad, int ShowFlags);
    typedef int   (__cdecl * LISTLOADNEXTFUNC)             (HWND ParentWin, HWND ListWin, char* FileToLoad, int ShowFlags);
    typedef int   (__cdecl * LISTNOTIFICATIONRECEIVEDFUNC) (HWND ListWin, int Message, WPARAM wParam, LPARAM lParam);
    typedef void  (__cdecl * LISTCLOSEWINDOWFUNC)          (HWND ListWin);
    typedef void  (__cdecl * LISTGETDETECTSTRINGFUNC)      (char* DetectString, int maxlen);

    static LISTLOADFUNC
    ListLoadFunc = (LISTLOADFUNC) GetProcAddress(hDLL, "ListLoad");
    static LISTLOADNEXTFUNC
    ListLoadNextFunc = (LISTLOADNEXTFUNC) GetProcAddress(hDLL, "ListLoadNext");
    static LISTNOTIFICATIONRECEIVEDFUNC
    ListNotificationReceivedFunc = (LISTNOTIFICATIONRECEIVEDFUNC) GetProcAddress(hDLL, "ListNotificationReceived");
    static LISTCLOSEWINDOWFUNC
    ListCloseWindowFunc = (LISTCLOSEWINDOWFUNC) GetProcAddress(hDLL, "ListCloseWindow");
    static LISTGETDETECTSTRINGFUNC
    ListGetDetectStringFunc = (LISTGETDETECTSTRINGFUNC) GetProcAddress(hDLL, "ListGetDetectString");


    switch (message)                  /* Handle the messages */
    {
        case WM_COMMAND:
        case WM_NOTIFY:
        case WM_MEASUREITEM:
        case WM_DRAWITEM:
            // Calling CallBack function of the plugin
            if (ListNotificationReceivedFunc)
                return ListNotificationReceivedFunc(pluginWindow, message, wParam, lParam);
            break;
        case WM_SIZE:
            sirka = LOWORD(lParam);
            dlzka = HIWORD(lParam);
            MoveWindow(pluginWindow, 0, 0, sirka, dlzka, TRUE);    // Toto potom pošle oknu pluginWindow správu WM_SIZE
            return 0;
        case WM_CREATE:
            pluginWindow = ListLoadFunc(hwnd, (char *) menoSuboru, 0);
            return 0;
        case WM_DESTROY:
            if (ListCloseWindowFunc)
                ListCloseWindowFunc(pluginWindow);
            else
                DestroyWindow(pluginWindow);
            FreeLibrary (hDLL);
            PostQuitMessage(EXIT_SUCCESS);       /* Send a WM_QUIT to the message queue */
            return 0;
    }

    return DefWindowProc(hwnd, message, wParam, lParam);
}
