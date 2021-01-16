#include<windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{
    WNDCLASSEX wndclass;
    HWND hwnd;
    MSG msg;
    TCHAR szAppName[] = TEXT("MyAppHelloWorld");

    wndclass.cbSize = sizeof(WNDCLASSEX);
    wndclass.style = CS_HREDRAW | CS_VREDRAW;
    wndclass.cbClsExtra = 0;
    wndclass.cbWndExtra = 0;
    wndclass.lpfnWndProc = WndProc;
    wndclass.hInstance = hInstance;
    wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
    wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    wndclass.lpszClassName = szAppName;
    wndclass.lpszMenuName = NULL;
    wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);


    RegisterClassEx(&wndclass);

    hwnd = CreateWindow(szAppName,
        TEXT("Hello World"),
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
    return ((int)msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
    HDC hdc;
    PAINTSTRUCT ps;
    RECT rc;
    TCHAR str[] = TEXT("Hello World..!!");
    static int iPainFlag = 0;

    switch (iMsg)
    {
       // r-red (255,0,0)
       // g- green(0,255,0)
       // b-blue(0,0,255)
       // c-cyan(0,255,255)
       // m-magenta(255,0,255)
       // y- yello(255,255,0)
       // left click-white (255,255,255)
       // right click - oraange (255,165,0)
    
    case WM_CHAR:
        
        switch (wParam)
        {
        case 'r':
        case 'R':iPainFlag = 1;
            InvalidateRect(hwnd, NULL, true);
            break;

        case 'g':
        case 'G':iPainFlag = 2;
            InvalidateRect(hwnd, NULL, true);
            break;
       
        case 'b':
        case 'B':iPainFlag = 3;
            InvalidateRect(hwnd, NULL, true);
            break;

        case 'c':
        case 'C':iPainFlag = 4;
            InvalidateRect(hwnd, NULL, true);
            break;

        case 'm':
        case 'M':iPainFlag = 5;
            InvalidateRect(hwnd, NULL, true);
            break;

        case 'y':
        case 'Y':iPainFlag = 6;
            InvalidateRect(hwnd, NULL, true);
            break;
        }
        break;

    case WM_PAINT:
        GetClientRect(hwnd, &rc);
        hdc = BeginPaint(hwnd, &ps);
        SetBkColor(hdc, RGB(0, 0, 0));
        SetTextColor(hdc, RGB(255, 255, 255));

        if (iPainFlag ==1)
           SetTextColor(hdc, RGB(255, 0,0));
        else if(iPainFlag == 2)
            SetTextColor(hdc, RGB(0, 255, 0));
        else if (iPainFlag == 3)
           SetTextColor(hdc, RGB(0, 0, 255));
        else if (iPainFlag == 4)
         SetTextColor(hdc, RGB(0, 255, 255));
        else if (iPainFlag == 5)
         SetTextColor(hdc, RGB(255, 0, 255));
        else if (iPainFlag == 6)
         SetTextColor(hdc, RGB(255, 255, 0));

        DrawText(hdc, str, -1, &rc, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
        EndPaint(hwnd, &ps);

        break;


    case WM_LBUTTONDOWN:
        InvalidateRect(hwnd, NULL, true);
        GetClientRect(hwnd, &rc);
        hdc = BeginPaint(hwnd, &ps);
        SetBkColor(hdc, RGB(0, 0, 0));
        SetTextColor(hdc, RGB(255, 255, 255));
        DrawText(hdc, str, -1, &rc, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
        EndPaint(hwnd, &ps);
        break;

    case WM_RBUTTONDOWN:
        InvalidateRect(hwnd, NULL, true);
        GetClientRect(hwnd, &rc);
        hdc = BeginPaint(hwnd, &ps);
        SetBkColor(hdc, RGB(0, 0, 0));
        SetTextColor(hdc, RGB(255, 165, 0));
        DrawText(hdc, str, -1, &rc, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
        EndPaint(hwnd, &ps);
        break;

    case WM_DESTROY:
       
        PostQuitMessage(0);
        break;

    }
    return (DefWindowProc(hwnd, iMsg, wParam, lParam));
}