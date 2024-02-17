#pragma once

#include <windows.h>
#include <windowsx.h>
#include <tchar.h>
#include "Engine.h"

struct WinInitData {
    HINSTANCE hInstance;
    HINSTANCE hPrevInstance;
    LPSTR lpCmdLine;
    int nCmdShow;
};

struct WindowProperty {
    int x;
    int y;
    RECT rect;
};

class Window
{
private:

    WinInitData* initData = nullptr;

    static LRESULT CALLBACK WindowProc(HWND hWnd,
        UINT message,
        WPARAM wParam,
        LPARAM lParam);
public:
    
    Window(WinInitData *initData);
    ~Window();

    LRESULT OpenWindow(WindowProperty winProperty);
};

