#pragma once

//stringとfunction
#include <string>
#include <functional>

//UIBase
#include "../UIBase.h"

class Button : public UIBase
{
public:

    Button();

    void Update() override;

    void Draw() override;

	// ボタンのテキストを設定する
    void SetText(const std::string& text);

    // ボタンの画像を設定する
    void SetImage(int graphHandle);

	// ボタンの有効状態を設定する
    void SetEnabled(bool enabled);

	// ボタンが有効かを取得する
    bool IsEnabled() const;

	// ボタンがホバーされているかを取得する
    bool IsHovered() const;

	// ボタンが押されているかを取得する
    bool IsPressed() const;

	// ボタンがクリックされたときのコールバックを設定する
    void SetOnClick(std::function<void()> callback);

private:

    // ボタンのテキスト
    std::string m_text;

    // ボタンの画像ハンドル
    int m_graphHandle = -1;

    // ボタンの有効状態
    bool m_enabled = true;

    // ボタンがホバーされているか
    bool m_hovered = false;

    // ボタンが押されているか
    bool m_pressed = false;

    // ボタンが有効か
    std::function<void()> m_onClick;
};