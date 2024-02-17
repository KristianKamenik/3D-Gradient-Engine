#pragma once

#include <d3d11.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>
#include "RenderPipeline.h"
#include "PrimitiveObjects.h"

#pragma comment (lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")

struct ConstantBuffer
{
	DirectX::XMMATRIX World;
};
struct ColorBuffer
{
	DirectX::XMFLOAT4 colorShift;
};

class Graphics
{
private:
	const Color CLEAR_COLOR = { 0.0f, 0.2f, 0.4f, 1.0f };
	IDXGISwapChain* swapchain = nullptr;
	ID3D11Device* dev = nullptr;
	ID3D11DeviceContext* devcon = nullptr;
	ID3D11RenderTargetView* backbuffer = nullptr;

	ID3D11Buffer* pVBuffer = nullptr;
	ID3D11Buffer* pVCubeBuffer = nullptr;
	ID3D11Buffer* pConstantBuffer = nullptr;
	ID3D11Buffer* colorBuffer = nullptr;

	IRenderPipeline* renderPipeline = nullptr;

	DirectX::XMMATRIX worldMatrix;

	int width;
	int height;

	const float* ConvertToFloatArr(const Color color);
	HRESULT InitGraphics(void);
	HRESULT TransformVertices(void);
	HRESULT GradientChange(void);
	HRESULT InitD3D(HWND hWnd);
	void InitViewport();
	ColorBuffer GetColorBuffer();
	template <typename T> HRESULT MapBuffer(ID3D11Buffer* cBuffer, T* cb, UINT size);
	HRESULT CreateBufferDW(ID3D11Buffer** cBuffer, UINT byteWidth, D3D11_BIND_FLAG bindFlags, D3D11_SUBRESOURCE_DATA* initData);
	void ReleaseBuffer(ID3D11Buffer* cBuffer);
	void SetVertexBuffer(ID3D11Buffer** verBuffer, int countV);

	HRESULT DrawPlane(ID3D11Buffer** verBuffer);
	HRESULT DrawCube(ID3D11Buffer** verBuffer);

public:
	Graphics(int width, int height);
	Graphics(int width, int height, IRenderPipeline* renderer);

	HRESULT Init(HWND hWnd);

	void SetWorldMatrix(DirectX::XMMATRIX matrix);
	void CleanD3D(void);
	HRESULT RenderFrame(void);
};

