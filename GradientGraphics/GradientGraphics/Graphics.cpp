#include "Graphics.h"

const float* Graphics::ConvertToFloatArr(const Color color)
{
    return new float[4]{ color.R,color.G , color.B , color.A };
}

Graphics::Graphics(int width, int height) : 
    width(width), 
    height(height), 
    renderPipeline(new DefaultRenderPipeline()),
    worldMatrix(DirectX::XMMatrixIdentity())
{}

HRESULT Graphics::Init(HWND hWnd)
{
    HRESULT hr = InitD3D(hWnd);
    if (FAILED(hr))
    {
        return hr;
    }

    InitViewport();
    hr = renderPipeline->InitPipeline(dev, devcon);
    if (FAILED(hr))
    {
        return hr;
    }

    hr = InitGraphics();
    if (FAILED(hr))
    {
        return hr;
    }

    return S_OK;
}

Graphics::Graphics(int width, int height, IRenderPipeline *renderer) : 
    width(width), 
    height(height), 
    renderPipeline(renderer),
    worldMatrix(DirectX::XMMatrixIdentity())
{}

void Graphics::SetWorldMatrix(DirectX::XMMATRIX matrix) {
    worldMatrix = matrix;
}

HRESULT Graphics::InitD3D(HWND hWnd)
{
    DXGI_SWAP_CHAIN_DESC scd;

    ZeroMemory(&scd, sizeof(DXGI_SWAP_CHAIN_DESC));

    scd.BufferCount = 1;                                    
    scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;     
    scd.BufferDesc.Width = width;
    scd.BufferDesc.Height = height;
    scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;      
    scd.OutputWindow = hWnd;                               
    scd.SampleDesc.Count = 4;                               
    scd.Windowed = TRUE;                                   
    scd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

    HRESULT hr = D3D11CreateDeviceAndSwapChain(NULL,
        D3D_DRIVER_TYPE_HARDWARE,
        NULL,
        NULL,
        NULL,
        NULL,
        D3D11_SDK_VERSION,
        &scd,
        &swapchain,
        &dev,
        NULL,
        &devcon);
    if (FAILED(hr))
    {
        return hr;
    }

    ID3D11Texture2D* pBackBuffer = nullptr;
    hr = swapchain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
    if (FAILED(hr))
    {
        return hr;
    }
    if (pBackBuffer == NULL)
    {
        return E_POINTER;
    }

    hr = dev->CreateRenderTargetView(pBackBuffer, NULL, &backbuffer);
    if (FAILED(hr))
    {
        return hr;
    }
    pBackBuffer->Release();

    devcon->OMSetRenderTargets(1, &backbuffer, NULL);

    return S_OK;
}

void Graphics::InitViewport()
{
    D3D11_VIEWPORT viewport;
    ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));

    viewport.TopLeftX = 0;
    viewport.TopLeftY = 0;
    viewport.Width = static_cast<float>(width);
    viewport.Height = static_cast<float>(height);

    devcon->RSSetViewports(1, &viewport);
}

void Graphics::CleanD3D(void)
{
    if (swapchain)
    {
        swapchain->SetFullscreenState(FALSE, NULL);
        swapchain->Release();
    }
    if (renderPipeline)
        renderPipeline->Release();
    if(pVBuffer)
        pVBuffer->Release();
    if(pVCubeBuffer)
        pVCubeBuffer->Release();
    if(pConstantBuffer)
        pConstantBuffer->Release();
    if(colorBuffer)
        colorBuffer->Release();
    if(backbuffer)
        backbuffer->Release();
    if(dev)
        dev->Release();
    if(devcon)
        devcon->Release();
}

HRESULT Graphics::RenderFrame(void)
{
    devcon->ClearRenderTargetView(backbuffer, ConvertToFloatArr(CLEAR_COLOR));

    HRESULT hr = TransformVertices();
    if (FAILED(hr))
    {
        return hr;
    }

    hr = GradientChange();
    if (FAILED(hr))
    {
        return hr;
    }

    devcon->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    SetVertexBuffer(&pVBuffer, PLANE_COUNT);
    SetVertexBuffer(&pVCubeBuffer, CUBE_COUNT);

    hr = swapchain->Present(0, 0);
    if (FAILED(hr))
    {
        return hr;
    }

    return S_OK;
}

HRESULT Graphics::GradientChange(void)
{
    ReleaseBuffer(colorBuffer);

    ColorBuffer cb = GetColorBuffer();

    HRESULT hr = CreateBufferDW(&colorBuffer, sizeof(ColorBuffer), D3D11_BIND_CONSTANT_BUFFER, NULL);
    if (FAILED(hr))
    {
        return hr;
    }

    hr = MapBuffer<ColorBuffer>(colorBuffer, &cb, sizeof(ColorBuffer));
    if (FAILED(hr))
    {
        return hr;
    }

    devcon->PSSetConstantBuffers(1, 1, &colorBuffer);
    return S_OK;
}

ColorBuffer Graphics::GetColorBuffer()
{
    ColorBuffer cb = {};
    static float currentColorValue = 0;
    static int colorValueSign = 1;

    currentColorValue += 0.001f * colorValueSign;
    if (currentColorValue >= 0.5f)
    {
        colorValueSign = -1;
        currentColorValue = 0.5f;
    }
    else if (currentColorValue <= -0.5f)
    {
        colorValueSign = 1;
        currentColorValue = -0.5f;
    }
    cb.colorShift = DirectX::XMFLOAT4(
        currentColorValue,
        static_cast<float>(width),
        0,
        0);

    return cb;
}

HRESULT Graphics::InitGraphics(void)
{
    HRESULT hr = DrawPlane(&pVBuffer);
    if (FAILED(hr))
    {
        return hr;
    }

    hr = DrawCube(&pVCubeBuffer);
    if (FAILED(hr))
    {
        return hr;
    }
    return S_OK;
}

HRESULT Graphics::TransformVertices(void)
{
    ReleaseBuffer(pConstantBuffer);

    ConstantBuffer cb = {};
    cb.World = worldMatrix;

    D3D11_SUBRESOURCE_DATA initData = {};
    initData.pSysMem = &cb;

    HRESULT hr = CreateBufferDW(&pConstantBuffer, sizeof(ConstantBuffer), D3D11_BIND_CONSTANT_BUFFER, &initData);
    if (FAILED(hr))
    {
        return hr;
    }

    hr = MapBuffer<ConstantBuffer>(pConstantBuffer, &cb, sizeof(ConstantBuffer));
    if (FAILED(hr))
    {
        return hr;
    }

    devcon->VSSetConstantBuffers(0, 1, &pConstantBuffer);
    return S_OK;
}

HRESULT Graphics::DrawPlane(ID3D11Buffer** verBuffer)
{
    HRESULT hr = CreateBufferDW(verBuffer, sizeof(VERTEX) * PLANE_COUNT, D3D11_BIND_VERTEX_BUFFER, NULL);

    if (FAILED(hr))
    {
        return hr;
    }

    D3D11_MAPPED_SUBRESOURCE ms;
    hr = devcon->Map(*verBuffer, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &ms);

    if (FAILED(hr))
    {
        return hr;
    }

    memcpy(ms.pData, PLANE, sizeof(PLANE));
    devcon->Unmap(*verBuffer, NULL);
    
    return S_OK;
}

HRESULT Graphics::DrawCube(ID3D11Buffer** verBuffer)
{
    HRESULT hr = CreateBufferDW(verBuffer, sizeof(VERTEX) * CUBE_COUNT, D3D11_BIND_VERTEX_BUFFER, NULL);

    if (FAILED(hr))
    {
        return hr;
    }

    D3D11_MAPPED_SUBRESOURCE ms;
    hr = devcon->Map(*verBuffer, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &ms);

    if (FAILED(hr))
    {
        return hr;
    }

    memcpy(ms.pData, CUBE, sizeof(CUBE));
    devcon->Unmap(*verBuffer, NULL);

    return S_OK;
}

template <typename T> HRESULT Graphics::MapBuffer(ID3D11Buffer *cBuffer, T *cb, UINT size)
{
    if (cBuffer == NULL)
    {
        return E_POINTER;
    }

    D3D11_MAPPED_SUBRESOURCE mappedResource;
    HRESULT hr = devcon->Map(cBuffer, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &mappedResource);
    if (FAILED(hr))
    {
        return hr;
    }
    memcpy(mappedResource.pData, cb, size);
    devcon->Unmap(cBuffer, NULL);
    return S_OK;
}

HRESULT Graphics::CreateBufferDW(ID3D11Buffer** cBuffer, UINT byteWidth, D3D11_BIND_FLAG bindFlags, D3D11_SUBRESOURCE_DATA* initData)
{
    D3D11_BUFFER_DESC bufferDesc;
    ZeroMemory(&bufferDesc, sizeof(bufferDesc));

    bufferDesc.Usage = D3D11_USAGE_DYNAMIC;
    bufferDesc.ByteWidth = byteWidth;
    bufferDesc.BindFlags = bindFlags;
    bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

    HRESULT hr = dev->CreateBuffer(&bufferDesc, initData, cBuffer);
    if (FAILED(hr))
    {
        return hr;
    }
    return S_OK;
}

void Graphics::ReleaseBuffer(ID3D11Buffer* cBuffer)
{
    if (cBuffer)
    {
        cBuffer->Release();
        cBuffer = nullptr;
    }
}

void Graphics::SetVertexBuffer(ID3D11Buffer** verBuffer, int countV)
{
    UINT stride = sizeof(VERTEX);
    UINT offset = 0;
    devcon->IASetVertexBuffers(0, 1, verBuffer, &stride, &offset);

    devcon->Draw(countV, 0);
}
