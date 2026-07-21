#pragma once

// UIの基底クラス
// UIの位置、サイズ、表示状態を管理する
//ボタンと画像、ラベル、パネルを管理
class UIBase
{
public:

    virtual ~UIBase() = default;

    virtual void Update() {}

    virtual void Draw() {}

    void SetPosition(int x, int y);

    void SetSize(int width, int height);

    void SetVisible(bool visible);

    bool IsVisible() const;

    bool Contains(int mouseX, int mouseY) const;

    int GetX() const;

    int GetY() const;


protected:

	// UIの位置
    int x = 0;
    int y = 0;

    // UIのサイズ
    int width = 0;
    int height = 0;

	// UIの表示状態
    bool visible = true;
};