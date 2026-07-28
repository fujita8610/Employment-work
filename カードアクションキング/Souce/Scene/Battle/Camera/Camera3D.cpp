#include "Camera3D.h"

bool Camera3D::Init()
{
    // ­‚µÎ‚ßã‚©‚ç”Õ–Ê‚ğŒ©‚é
    m_position = VGet(0.0f, 700.0f, -700.0f);

    // ”Õ–Ê’†‰›‚ğŒ©‚é
    m_target = VGet(0.0f, 0.0f, 0.0f);

    // ã•ûŒü
    m_up = VGet(0.0f, 1.0f, 0.0f);

    Apply();

    return true;
}

void Camera3D::Update()
{
    // ¡‚ÍŒÅ’èƒJƒƒ‰
    Apply();
}

void Camera3D::Apply()
{
    SetCameraPositionAndTargetAndUpVec(
        m_position,
        m_target,
        m_up);
}

void Camera3D::Release()
{
    // ¡‚Íˆ—‚È‚µ
}

void Camera3D::SetPosition(const VECTOR& position)
{
    m_position = position;
}

void Camera3D::SetTarget(const VECTOR& target)
{
    m_target = target;
}

void Camera3D::SetUp(const VECTOR& up)
{
    m_up = up;
}

VECTOR Camera3D::GetPosition() const
{
    return m_position;
}

VECTOR Camera3D::GetTarget() const
{
    return m_target;
}

VECTOR Camera3D::GetUp() const
{
    return m_up;
}