#include "CardDrawAnimation.h"

#include "../../../Renderer/Hand/HandRenderer.h"

// コンストラクタ
CardDrawAnimation::CardDrawAnimation(HandRenderer* handRenderer, 
    float startX,float startY,float endX,float endY)
{
    m_handRenderer = handRenderer;

    m_startX = startX;
    m_startY = startY;

    m_endX = endX;
    m_endY = endY;

    m_currentX = startX;
    m_currentY = startY;
}

// アニメーション開始時
void CardDrawAnimation::OnStart()
{
    if (m_handRenderer == nullptr)
    {
        return;
    }
    m_handRenderer->SetDrawAnimationPosition(m_startX,m_startY);
    m_handRenderer->SetDrawAnimationVisible(true);
}

// アニメーション更新
void CardDrawAnimation::Update(float deltaTime)
{
    AnimationBase::Update(deltaTime);   // 基底クラスの更新
    float t = GetProgress();            // 進行度取得

    // イージング
    float easedT = 1.0f - (1.0f - t) * (1.0f - t);

    m_currentX = m_startX + (m_endX - m_startX) * easedT;    // X座標補間
    m_currentY = m_startY + (m_endY - m_startY) * easedT;    // Y座標補間

    if (m_handRenderer != nullptr)  // HandRendererへ座標を渡す
    {
        m_handRenderer->SetDrawAnimationPosition(m_currentX,m_currentY);
    }
}

// アニメーション終了時
void CardDrawAnimation::OnFinished()
{
    if (m_handRenderer == nullptr)
    {
        return;
    }

    m_handRenderer->SetDrawAnimationVisible(false);
}
