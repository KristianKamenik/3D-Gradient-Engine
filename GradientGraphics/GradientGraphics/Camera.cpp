#include "Camera.h"

Camera::Camera() :
    moveAxis(DirectX::XMFLOAT3(0, 0, 0)),
    rotation(DirectX::XMFLOAT3(0, 0, 0)),
    movemntSpeed(0.003f),
    rotationSpeed(0.2f)
{}

void Camera::SetMoveAxis(DirectX::XMFLOAT3 position){
    moveAxis = position;
}

void Camera::IncreaseRotationDG(DirectX::XMFLOAT3 rotation){
    this->rotation.x += ((rotation.x * rotationSpeed) / 360.0f) * DirectX::XM_2PI;
    this->rotation.y += ((rotation.y * rotationSpeed) / 360.0f) * DirectX::XM_2PI;
    this->rotation.z += ((rotation.z * rotationSpeed) / 360.0f) * DirectX::XM_2PI;
}

DirectX::XMMATRIX Camera::GetMatrix(int width, int height){

    DirectX::XMMATRIX world = DirectX::XMMatrixIdentity();
    DirectX::XMMATRIX viewMatrix = GetViewMatrix();
    DirectX::XMMATRIX projectionMatrix = GetPerspective(width, height);

    DirectX::XMMATRIX result = world * viewMatrix * projectionMatrix;

    return DirectX::XMMatrixTranspose(result);
}

DirectX::XMFLOAT3 Camera::GetRotation()
{
    return rotation;
}

DirectX::XMMATRIX Camera::GetPerspective(int width, int height)
{
    float fovDegrees = 90.0f;
    float fovRadians = (fovDegrees / 360.0f) * DirectX::XM_2PI;
    float aspectRatio = static_cast<float>(width) / static_cast<float>(height);
    float nearZ = 0.1f;
    float farZ = 1000.0f;
    return DirectX::XMMatrixPerspectiveFovLH(fovRadians, aspectRatio, nearZ, farZ);;
}

DirectX::XMVECTOR Camera::GetModifiedVector(const DirectX::XMVECTOR *main,const DirectX::XMFLOAT3 *axis)
{
    DirectX::XMFLOAT3 posFloat3;
    DirectX::XMStoreFloat3(&posFloat3, *main);
    posFloat3.x += axis->x * movemntSpeed;
    posFloat3.y += axis->y * movemntSpeed;
    posFloat3.z += axis->z * movemntSpeed;
    return DirectX::XMLoadFloat3(&posFloat3);
}

DirectX::XMMATRIX Camera::GetViewMatrix()
{
    static DirectX::XMVECTOR eyePos = DirectX::XMVectorSet(0.0f, 0.0f, -1.5f, 0.0f);
    eyePos = GetModifiedVector(&eyePos, &moveAxis);

    static DirectX::XMVECTOR lookAtPos = eyePos;
    lookAtPos = DirectX::XMVectorAdd(lookAtPos, DirectX::XMVectorSet(0.0f, 0.0f, 1.5f, 0.0f));

    static DirectX::XMVECTOR upVector = DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);

    DirectX::XMMATRIX result = DirectX::XMMatrixLookAtLH(eyePos, lookAtPos, upVector);
    return result * GetRotationMatrix();
}

DirectX::XMMATRIX Camera::GetRotationMatrix()
{
    DirectX::XMMATRIX pitchMatrix = DirectX::XMMatrixRotationX(rotation.x);
    DirectX::XMMATRIX yawMatrix = DirectX::XMMatrixRotationY(rotation.y);
    DirectX::XMMATRIX rollMatrix = DirectX::XMMatrixRotationZ(rotation.z);

    return pitchMatrix * yawMatrix * rollMatrix;
}
