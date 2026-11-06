#include "AnimationBase.h"

// コンストラクタ
AnimationBase::AnimationBase()
{
}

// アニメーション開始
void AnimationBase::Start(float duration)
{
    m_duration = duration;

    m_elapsedTime = 0.0f;

    m_progress = 0.0f;

    m_isPlaying = true;

    m_isFinished = false;

    OnStart();
}

// アニメーション更新
void AnimationBase::Update(float deltaTime)
{
    if (!m_isPlaying || m_isFinished)
    {
        return;
    }

    // 経過時間を加算
    m_elapsedTime += deltaTime;

    // 進行度を計算
    if (m_duration <= 0.0f)
    {
        m_progress = 1.0f;
    }
    else
    {
        m_progress = m_elapsedTime / m_duration;
    }

    // 進行度を0～1に制限
    if (m_progress >= 1.0f)
    {
        m_progress = 1.0f;

        m_isPlaying = false;

        m_isFinished = true;

        OnFinished();
    }
}

// 終了判定
bool AnimationBase::IsFinished() const
{
    return m_isFinished;
}

// 再生中か
bool AnimationBase::IsPlaying() const
{
    return m_isPlaying;
}

// 進行度取得
float AnimationBase::GetProgress() const
{
    return m_progress;
}