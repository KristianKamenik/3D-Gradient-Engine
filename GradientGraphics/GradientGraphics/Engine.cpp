#include "Engine.h"

Engine& Engine::GetInstance()
{
    static Engine instance;
    return instance;
}

Engine::Engine()
{}

LRESULT Engine::StartEngine(WinInitData initData)
{
    WindowProperty property{ 0, 0, RECT {0,0,SCREEN_WIDTH,SCREEN_HEIGHT} };

    windows = new Window(&initData);
    graphic = new Graphics(SCREEN_WIDTH, SCREEN_HEIGHT);
    camera = new Camera();

    LRESULT result = windows->OpenWindow(property);
    Engine::GetInstance().Exit();
    return result;
}

HRESULT Engine::Start(HWND hWnd)
{
    return graphic->Init(hWnd);
}

HRESULT Engine::Update(void)
{
    LookControl();
    MoveControl();
    graphic->SetWorldMatrix(camera->GetMatrix(SCREEN_WIDTH, SCREEN_HEIGHT));
    return graphic->RenderFrame();
}

void Engine::Exit(void)
{
    graphic->CleanD3D();
    delete camera;
    delete graphic;
    delete windows;
}

Engine& Engine::operator=(const Engine&)
{
    return GetInstance();
}

void Engine::LookControl()
{
    DirectX::XMFLOAT3 axis = F3ZERO;
    if (GetKeyState(VK_RIGHT) & 0x8000)
    {
        axis.y -= 1;
    }
    if (GetKeyState(VK_LEFT) & 0x8000)
    {
        axis.y += 1;
    }
    camera->IncreaseRotationDG(axis);
    
}

void Engine::MoveControl()
{
    DirectX::XMFLOAT3 axis = F3ZERO;
    if (GetKeyState('W') & 0x8000)
    {
        axis.z += DirectX::XMScalarCos(camera->GetRotation().y);
        axis.x -= DirectX::XMScalarSin(camera->GetRotation().y);
    }
    if (GetKeyState('S') & 0x8000)
    {
        axis.z -= DirectX::XMScalarCos(camera->GetRotation().y);
        axis.x += DirectX::XMScalarSin(camera->GetRotation().y);
    }
    if (GetKeyState('D') & 0x8000)
    {
        axis.x += DirectX::XMScalarCos(camera->GetRotation().y);
        axis.z += DirectX::XMScalarSin(camera->GetRotation().y);
    }
    if (GetKeyState('A') & 0x8000)
    {
        axis.x -= DirectX::XMScalarCos(camera->GetRotation().y);
        axis.z -= DirectX::XMScalarSin(camera->GetRotation().y);
    }
    if (GetKeyState(VK_SPACE) & 0x8000)
    {
        axis.y += 1;
    }
    if (GetKeyState(VK_CONTROL) & 0x8000)
    {
        axis.y -= 1;
    }
    camera->SetMoveAxis(axis);
}
