#include<windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
DWORD WINAPI ThreadProcOne(LPVOID);
DWORD WINAPI ThreadProcTwo(LPVOID);

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
    wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
    wndclass.hbrBackground = (HBRUSH)COLOR_WINDOW;;
    wndclass.lpszClassName = szAppName;
    wndclass.lpszMenuName = NULL;
    wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

    RegisterClassEx(&wndclass);

    hwnd = CreateWindow(szAppName,
        TEXT("Threading"),
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

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
    static HANDLE hThreadOne = NULL;
    static HANDLE hThreadTwo = NULL;

    switch (iMsg)
    {

    case WM_CREATE:
        hThreadOne = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadProcOne, (LPVOID)hWnd, 0, NULL);
        hThreadTwo = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadProcTwo, (LPVOID)hWnd, 0, NULL);
        break;

    case WM_LBUTTONDOWN:
        MessageBox(hWnd, TEXT("This is mutithrading application"), TEXT("Message"), MB_OK);
        break;

    case WM_DESTROY:
        if (hThreadOne)
        {
            CloseHandle(hThreadOne);
            hThreadOne = NULL;
        }
        if (hThreadTwo)
        {
            CloseHandle(hThreadTwo);
            hThreadTwo = NULL;
        }
        PostQuitMessage(0);
        break;
    }
    return (DefWindowProc(hWnd, iMsg, wParam, lParam));
}

DWORD WINAPI ThreadProcOne(LPVOID Param)
{
    HDC hdc;
    long i = 0;
    TCHAR str[255];

    hdc = GetDC((HWND)Param);
    for(i = 0; i < 2147483647; i++)
    {
        wsprintf(str, TEXT("Thread 1: Increasing order : %ld "), i);
        TextOut(hdc, 5, 5, str, wcslen(str));
    }
    ReleaseDC((HWND)Param, hdc);
    return 0;
}

DWORD WINAPI ThreadProcTwo(LPVOID Param)
{
    HDC hdc;
    long i = 0;
    TCHAR str[255];
    hdc = GetDC((HWND)Param);

    for (i = 2147483647; i >= 0; i--)
    {
        wsprintf(str, TEXT("Thread 1: Decreasing order : %ld "), i);
        TextOut(hdc, 5, 25, str, wcslen(str));
    }
    ReleaseDC((HWND)Param, hdc);
    return 0;
}
