#pragma once

#include "../../AnimationBase.h"

class HandRenderer;

// カードドローアニメーション
class CardDrawAnimation : public AnimationBase
{
public:

    // コンストラクタ
    CardDrawAnimation(HandRenderer* handRenderer, 
        float startX,float startY,float endX,float endY);

    void Update(float deltaTime) override;    // アニメーション更新

protected:

    void OnStart() override;    // アニメーション開始時
    void OnFinished() override;  // アニメーション終了時

private:

	HandRenderer* m_handRenderer = nullptr; // 手札描画クラスへの参照

    // 開始位置
    float m_startX = 0.0f;
    float m_startY = 0.0f;

    // 終了位置
    float m_endX = 0.0f;
    float m_endY = 0.0f;

    // 現在位置
    float m_currentX = 0.0f;
    float m_currentY = 0.0f;
};