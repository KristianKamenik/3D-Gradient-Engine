#include "RenderPipeline.h"

HRESULT DefaultRenderPipeline::InitPipeline(
    ID3D11Device* dev,
    ID3D11DeviceContext* devcon){

    ID3D10Blob* VS, * PS;

    HRESULT hr = D3DCompileFromFile(L"Shaders.shader", nullptr, nullptr, "VShader", "vs_4_0", 0, 0, &VS, nullptr);
    if (FAILED(hr))
    {
        return hr;
    }
    hr = D3DCompileFromFile(L"Shaders.shader", nullptr, nullptr, "PShader", "ps_4_0", 0, 0, &PS, nullptr);
    if (FAILED(hr))
    {
        return hr;
    }

    hr = dev->CreateVertexShader(VS->GetBufferPointer(), VS->GetBufferSize(), NULL, &pVS);
    if (FAILED(hr))
    {
        return hr;
    }
    hr = dev->CreatePixelShader(PS->GetBufferPointer(), PS->GetBufferSize(), NULL, &pPS);
    if (FAILED(hr))
    {
        return hr;
    }

    devcon->VSSetShader(pVS, 0, 0);
    devcon->PSSetShader(pPS, 0, 0);

    D3D11_INPUT_ELEMENT_DESC ied[] =
    {
        {"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
        {"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
    };

    hr = dev->CreateInputLayout(ied, 2, VS->GetBufferPointer(), VS->GetBufferSize(), &pLayout);
    if (FAILED(hr))
    {
        return hr;
    }
    devcon->IASetInputLayout(pLayout);

    return S_OK;
}

void IRenderPipeline::Release()
{
    if(pLayout)
        pLayout->Release();
    if(pVS)
        pVS->Release();
    if(pPS)
        pPS->Release();
}
