#include <windows.h>
#include <commctrl.h>
#include "WindowProc.h"
#include "NaplnStrukturuWndClassEx.h"
#include "Constants.h"


int WINAPI WinMain (HINSTANCE  hThisInstance, HINSTANCE hPrevInstance, LPSTR lpszArgument, int  nCmdShow)
{
    HWND        hwnd;               /* This is the handle for our window */
    MSG         message;            /* Here message to the application are saved */
    WNDCLASSEX  wndClassEx;         /* Data structure for the windowclass */

    NaplnStrukturuWndClassEx(&wndClassEx, hThisInstance, szClassName);

    /* Register the window class, and if it fails quit the program */
    if (!RegisterClassEx(&wndClassEx))
        return EXIT_FAILURE;

    LoadLibrary(TEXT("Riched20.dll"));            // Bez tohto to nešlo!

//    INITCOMMONCONTROLSEX icce;
//    icce.dwSize = sizeof (INITCOMMONCONTROLSEX);
//    icce.dwICC  = ICC_STANDARD_CLASSES | ICC_LISTVIEW_CLASSES | ICC_TAB_CLASSES;
//    InitCommonControlsEx(&icce);

    /* The class is registered, let's create the program main window */
    hwnd = CreateWindowEx (
           0,                   /* Extended possibilities for variation */
           szClassName,         /* Classname */
           szClassName,         /* Title Text */
           WS_OVERLAPPEDWINDOW, /* default window */
           CW_USEDEFAULT,       /* Windows decides the position */
           CW_USEDEFAULT,       /* where the window ends up on the screen */
           900, 660,            /* The programs width and height in pixels */
           HWND_DESKTOP,        /* The window is a child-window to desktop */
           NULL,                /* No menu */
           hThisInstance,       /* Program Instance handler */
           NULL                 /* No Window Creation data */
           );

    /* Make the window visible on the screen */
    ShowWindow  (hwnd, nCmdShow);
    UpdateWindow(hwnd);                 // Ide to aj bez tohto

    /* Run the message loop. It will run until GetMessage() returns 0 */
    while (GetMessage(&message, NULL, 0, 0))
    {
        /* Translate virtual-key message into character message */
        TranslateMessage(&message);

        /* Send message to WindowProcedure */
        DispatchMessage (&message);
    }

    /* The program return value is 0 - the value that PostQuitMessage() gave */
    return message.wParam;
}

