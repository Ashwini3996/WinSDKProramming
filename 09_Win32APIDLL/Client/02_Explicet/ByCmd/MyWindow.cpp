#include<windows.h>
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{
    WNDCLASSEX wndclass;
    HWND hwnd;
    MSG msg;
    TCHAR szAppName[] = TEXT("MyExplicetDLL");

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
        TEXT("Explicet Linking"),
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
    HMODULE hDll = NULL;
    typedef int (*MakeSquareFunctionPointr)(int); //Function pointer declaration cha typedef
    MakeSquareFunctionPointr makeSquareFunctionPointr = NULL;
    int i = 5, j = 0;
    TCHAR str[255];
    

    switch (iMsg)
    {
    case WM_CREATE://Me load karnar aahe Library Mhanun ha API
        hDll = LoadLibrary(TEXT("08_MyMath.dll"));//dll file name
        if (hDll == NULL)
        {
            MessageBox(hwnd, TEXT("Load Libray Failed !"), TEXT("Eror"), MB_OK);
            DestroyWindow(hwnd);//ha API intranaly WM_DESTROY pathvto
        }

        makeSquareFunctionPointr = (MakeSquareFunctionPointr)GetProcAddress(hDll, "MakeSquare");
        if (makeSquareFunctionPointr == NULL)
        {
            FreeLibrary(hDll);
            MessageBox(hwnd, TEXT("GetProcAddress Failed !"), TEXT("Eror"), MB_OK);
        }

        j = makeSquareFunctionPointr(i);
        wsprintf(str, TEXT("The square of %d is :%d"), i, j);
        MessageBox(hwnd, str, TEXT("Message"), MB_OK);
        FreeLibrary(hDll);
        break;

    case WM_DESTROY:PostQuitMessage(0);
        break;
    }
    return (DefWindowProc(hwnd, iMsg, wParam, lParam));
}

