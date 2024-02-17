#pragma once

#include "Window.h"
#include "Graphics.h"
#include "Camera.h"

#define SCREEN_WIDTH  1680
#define SCREEN_HEIGHT 1050

struct WinInitData;
class Camera;
class Window;
class Graphics;

class Engine
{
public:
	static Engine& GetInstance();

	LRESULT StartEngine(WinInitData initData);
	HRESULT Start(HWND hWnd);
	HRESULT Update(void);
	void Exit(void);
private:

	const DirectX::XMFLOAT3 F3ZERO = DirectX::XMFLOAT3(0, 0, 0);

	Camera* camera = nullptr;
	Window* windows = nullptr;
	Graphics* graphic = nullptr;

	Engine();
	Engine(const Engine&);
	Engine& operator=(const Engine&);

	void LookControl();
	void MoveControl();
};

