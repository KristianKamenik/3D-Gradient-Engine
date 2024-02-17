#pragma once
#include <d3d11.h>
#include <d3dcompiler.h>

class IRenderPipeline{
protected:
	ID3D11InputLayout* pLayout = nullptr;
	ID3D11VertexShader* pVS = nullptr;
	ID3D11PixelShader* pPS = nullptr;
public:
	virtual HRESULT InitPipeline(
		ID3D11Device* dev,
		ID3D11DeviceContext* devcon) = 0;
	void Release();
};

class DefaultRenderPipeline : public IRenderPipeline{
public:
	HRESULT InitPipeline(
		ID3D11Device* dev,
		ID3D11DeviceContext* devcon) override;
};