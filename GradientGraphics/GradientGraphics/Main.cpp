#include "Engine.h"

int WINAPI WinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPSTR lpCmdLine,
    _In_ int nCmdShow)
{
    WinInitData initData{
    hInstance,
    hPrevInstance,
    lpCmdLine,
    nCmdShow
    };
    return static_cast<int>(Engine::GetInstance().StartEngine(initData));
}