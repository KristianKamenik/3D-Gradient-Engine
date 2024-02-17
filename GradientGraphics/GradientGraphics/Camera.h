#pragma once
#include <d3d11.h>
#include <DirectXMath.h>

class Camera
{
public:
    Camera();

    void SetMoveAxis(DirectX::XMFLOAT3 position);
    void IncreaseRotationDG(DirectX::XMFLOAT3 rotation);

    DirectX::XMMATRIX GetMatrix(int width, int height);

    DirectX::XMFLOAT3 GetRotation();

private:
    DirectX::XMMATRIX GetPerspective(int width, int height);
    DirectX::XMVECTOR GetModifiedVector(const DirectX::XMVECTOR *main,const DirectX::XMFLOAT3 *axis);
    DirectX::XMMATRIX GetViewMatrix();
    DirectX::XMMATRIX GetRotationMatrix();

    float movemntSpeed;
    float rotationSpeed;

    DirectX::XMFLOAT3 moveAxis;
    DirectX::XMFLOAT3 rotation;
};

