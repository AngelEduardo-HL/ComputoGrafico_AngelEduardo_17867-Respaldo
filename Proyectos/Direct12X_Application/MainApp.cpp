#include <windows.h>
#include "AppDirect12X.h"

LRESULT CALLBACK WindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;


    default:
        return DefWindowProc(hWnd, msg, wParam, lParam);
    }
}

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR, int nCmdShow)
{
    const int width = 800;
    const int height = 800;
    const wchar_t CLASS_NAME[] = L"DirectX12TriangleX";

    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;
    wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);

    if (!RegisterClass(&wc))
        return -1;

    HWND hwnd = CreateWindowEx(
        0,                      
        CLASS_NAME,             
        L"DirectX 12 Triangle",
        WS_OVERLAPPEDWINDOW,    
        CW_USEDEFAULT, CW_USEDEFAULT, width, height,
        nullptr, nullptr, hInstance, nullptr
    );

    if (!hwnd)
        return -1;

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    ApplicationDirect12X app;
    app.AttachHWNDX(hwnd, width, height);
    app.SetUpX();

    MSG msg = {};
    bool running = true;
    while (running)
    {
        while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            if (msg.message == WM_QUIT)
            {
                running = false;
                break;
            }
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        app.UpdateX();
        app.DrawX();
    }

    return 0;
}