#include "Button.h"

#include "DxLib.h"

// InputManager
#include"../../Manager/Input/InputManager.h"

Button::Button()
{
}

void Button::Update()
{
	// ボタンが表示されていない場合、または無効な場合は処理をスキップ
    if (!visible || !m_enabled)
        return;

	// マウスの座標を取得
    int mx = InputManager::GetInstance().GetMouseX();
    int my = InputManager::GetInstance().GetMouseY();

	// ボタンがホバーされているかを判定
    m_hovered = Contains(mx, my);

	// ボタンが押されているかを判定
    m_pressed = false;

	// ボタンがホバーされていて、左クリックが押された場合
    if (m_hovered &&
        InputManager::GetInstance().IsMouseDown(MOUSE_INPUT_LEFT))
    {
		// ボタンが押された状態にする
        m_pressed = true;

		// ボタンがクリックされたときのコールバックを呼び出す
        if (m_onClick)
        {
            m_onClick();
        }
    }
}

void Button::Draw()
{
	// ボタンが表示されていない場合は描画をスキップ
    if (!visible)
        return;

    if (m_graphHandle != -1)
    {
        DrawGraph(x, y, m_graphHandle, TRUE);
    }
    else
    {
        int color = m_hovered
            ? GetColor(120, 120, 120)
            : GetColor(80, 80, 80);

        DrawBox(
            x,
            y,
            x + width,
            y + height,
            color,
            TRUE);

        DrawBox(
            x,
            y,
            x + width,
            y + height,
            GetColor(255, 255, 255),
            FALSE);

        DrawString(
            x + 15,
            y + 10,
            m_text.c_str(),
            GetColor(255, 255, 255));
    }
}

/// ボタンのテキストを設定する
void Button::SetText(const std::string& text)
{
    m_text = text;
}

// ボタンの画像を設定する
void Button::SetEnabled(bool enabled)
{
    m_enabled = enabled;
}

// ボタンが有効かを取得する
void Button::SetOnClick(std::function<void()> callback)
{
    m_onClick = callback;
}

//画像の設定
void Button::SetImage(int graphHandle)
{
    m_graphHandle = graphHandle;
}

// ボタンがホバーされているかを取得する
bool Button::IsHovered() const
{
    return m_hovered;
}

// ボタンが押されているかを取得する
bool Button::IsPressed() const
{
    return m_pressed;
}

// ボタンが有効かを取得する
bool Button::IsEnabled() const
{
    return m_enabled;
}