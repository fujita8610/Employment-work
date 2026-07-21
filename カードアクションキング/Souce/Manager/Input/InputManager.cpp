#include "InputManager.h"
#include "DxLib.h"

//cstring
#include <cstring>

InputManager& InputManager::GetInstance()
{
    //シングルトン
    static InputManager instance;
    return instance;
}

void InputManager::Update()
{
	//前回のキー状態を保存
    memcpy(m_oldKey, m_nowKey, sizeof(m_nowKey));

	//現在のキー状態を取得
    GetHitKeyStateAll(m_nowKey);

	//前回のマウス状態を保存
    m_oldMouse = m_nowMouse;
	//現在のマウス状態を取得
    m_nowMouse = GetMouseInput();

    //現在のマウス座標を取得
    GetMousePoint(&m_mouseX, &m_mouseY);
}

// キーが押されているかを判定する
bool InputManager::IsKeyPressed(int key) const
{
    return m_nowKey[key];
}

// キーが押された瞬間かを判定する
bool InputManager::IsKeyDown(int key) const
{
    return m_nowKey[key] && !m_oldKey[key];
}

// キーが離された瞬間かを判定する
bool InputManager::IsKeyUp(int key) const
{
    return !m_nowKey[key] && m_oldKey[key];
}

// マウスのX座標を取得する
int InputManager::GetMouseX() const
{
    return m_mouseX;
}

// マウスのY座標を取得する
int InputManager::GetMouseY() const
{
    return m_mouseY;
}

// マウスボタンが押されているかを判定する
bool InputManager::IsMousePressed(int button) const
{
    return (m_nowMouse & button) != 0;
}

// マウスボタンが押された瞬間かを判定する
bool InputManager::IsMouseDown(int button) const
{
    return (m_nowMouse & button) && !(m_oldMouse & button);
}

// マウスボタンが離された瞬間かを判定する
bool InputManager::IsMouseUp(int button) const
{
    return !(m_nowMouse & button) && (m_oldMouse & button);
}