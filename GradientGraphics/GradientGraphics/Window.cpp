#include "Window.h"

LRESULT CALLBACK Window::WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
        case WM_DESTROY:
        {
            PostQuitMessage(0);
            return 0;
        } break;
    }
    return DefWindowProc(hWnd, message, wParam, lParam);
}

Window::Window(WinInitData* initData)
{
    this->initData = initData;
}

Window::~Window()
{
    initData = nullptr;
}

LRESULT Window::OpenWindow(WindowProperty winProperty)
{
    HWND hWnd;
    WNDCLASSEX wc;

    ZeroMemory(&wc, sizeof(WNDCLASSEX));

    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = initData->hInstance;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.lpszClassName = L"WindowClass1";

    RegisterClassEx(&wc);

    AdjustWindowRect(&winProperty.rect, WS_OVERLAPPEDWINDOW, FALSE);

    hWnd = CreateWindowEx(NULL,
        L"WindowClass1",    
        L"Gradient",  
        WS_OVERLAPPEDWINDOW,    
        winProperty.x,   
        winProperty.y,    
        winProperty.rect.right - winProperty.rect.left,
        winProperty.rect.bottom - winProperty.rect.top,
        NULL,    
        NULL,    
        initData->hInstance,    
        NULL);    

    ShowWindow(hWnd, initData->nCmdShow);

    MSG msg = { 0 };
    if (FAILED(Engine::GetInstance().Start(hWnd)))
    {
        MessageBox(nullptr, _T("Gradient Engine failed map/create buffers or other unexpected error. Program will safely quit."), _T("Error"), MB_OK);
        msg.message = WM_QUIT;
        return msg.wParam;
    }

    while (TRUE)
    {
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
            if (msg.message == WM_QUIT)
                break;
        }
        if (FAILED(Engine::GetInstance().Update()))
        {
            MessageBox(nullptr, _T("Gradient Engine failed map/create buffers or other unexpected error. Program will safely quit."), _T("Error"), MB_OK);
            msg.message = WM_QUIT;
            break;
        }
    }

    return msg.wParam;
}
