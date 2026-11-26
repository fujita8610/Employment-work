#pragma once

#include "SceneBase.h"

class TitleScene : public SceneBase
{
public:

    // 初期化
    bool Init() override;

    // 更新
    void Update() override;

    // 描画
    void Draw() override;

    // 解放
    void Release() override;

private:

    // ボタン判定
    bool IsMouseInButton(
        int mouseX,
        int mouseY,
        int x,
        int y,
        int width,
        int height
    );

};