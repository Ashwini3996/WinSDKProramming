#include<windows.h>
#define MYTIMER 102
#include"MyWindow.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
int iPaintFlag = 0;
//WinMain()

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{
    WNDCLASSEX wndclass;
    HWND hwnd;
    MSG msg;
    TCHAR szAppName[] = TEXT("MyAPP");

    wndclass.cbSize = sizeof(WNDCLASSEX);
    wndclass.style = CS_HREDRAW | CS_VREDRAW;
    wndclass.cbClsExtra = 0;
    wndclass.cbWndExtra = 0;
    wndclass.lpfnWndProc = WndProc;
    wndclass.hInstance = hInstance;
    wndclass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(MYICON));
    wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
    wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    wndclass.lpszClassName = szAppName;
    wndclass.lpszMenuName = NULL;
    wndclass.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(MYICON));

    RegisterClassEx(&wndclass);

    hwnd = CreateWindow(szAppName,
        TEXT("First Window"),
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        NULL,
        NULL,
        hInstance,
        NULL);

    ShowWindow(hwnd, iCmdShow);
    UpdateWindow(hwnd);

    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return((int)msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
    //due re-enternt brush will create again again and to preseve the value make static and initialize in WM_CREATE
    static HBRUSH hBrush[8];
    HDC hdc;
    PAINTSTRUCT ps;
    RECT rc;
    TCHAR str[] = TEXT("Hello World..!!");
    static int iPainFlag = 0;


    switch (iMsg)
    {
    case WM_DESTROY:PostQuitMessage(0);
        break;

    case WM_CREATE:
        //we have craete once and used thrughtout the program
        if (iPaintFlag > 7)
            iPaintFlag = 0;

        hBrush[0] = CreateSolidBrush(RGB(255, 0, 0));
        hBrush[1] = CreateSolidBrush(RGB(0, 255, 0));
        hBrush[2] = CreateSolidBrush(RGB(0, 0, 255));
        hBrush[3] = CreateSolidBrush(RGB(255, 255, 0));
        hBrush[4] = CreateSolidBrush(RGB(255, 0, 255));
        hBrush[5] = CreateSolidBrush(RGB(0, 255, 255));
        hBrush[6] = CreateSolidBrush(RGB(255, 165, 0));
        hBrush[7] = CreateSolidBrush(RGB(255, 255, 255));
        SetTimer(hwnd, MYTIMER, 2000, NULL);
        break;

        //WM_TIMER is iteself is loop
    case WM_TIMER:
            KillTimer(hwnd, MYTIMER);
            iPaintFlag++;
            InvalidateRect(hwnd,NULL,TRUE);
            SetTimer(hwnd, MYTIMER, 2000, NULL);
            break;

       case WM_PAINT:
           GetClientRect(hwnd, &rc);
           hdc = BeginPaint(hwnd, &ps);
           SelectObject(hdc, hBrush[iPaintFlag]);
           FillRect(hdc, &rc, hBrush[iPaintFlag]);
           EndPaint(hwnd, &ps);
          break;
    }
    return (DefWindowProc(hwnd, iMsg, wParam, lParam));
}

//if(iPaintFlag == 0)
//{
// SelectObject(hdc, hBrush[0])
//}