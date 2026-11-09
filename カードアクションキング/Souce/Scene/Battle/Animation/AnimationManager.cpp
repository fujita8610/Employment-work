#include "AnimationManager.h"

#include <algorithm>

// 初期化
bool AnimationManager::Init()
{
    Clear();
    return true;
}

// アニメーション追加
void AnimationManager::AddAnimation(std::unique_ptr<AnimationBase> animation)
{
    if (animation == nullptr)
    {
        return;
    }

    m_animations.push_back(std::move(animation));
}

// 全アニメーション更新
void AnimationManager::Update(float deltaTime)
{
    // 登録されているアニメーションを更新
    for (const std::unique_ptr<AnimationBase>& animation : m_animations)
    {
        if (animation != nullptr)
        {
            animation->Update(deltaTime);
        }
    }

    // 終了したアニメーションを削除
    m_animations.erase(std::remove_if
    (m_animations.begin(),m_animations.end(),[]
    (const std::unique_ptr<AnimationBase>& animation)
            {
                return animation == nullptr || animation->IsFinished();
            }),

        m_animations.end());
}

// アニメーション再生中か
bool AnimationManager::IsPlaying() const
{
    return !m_animations.empty();
}

// 全アニメーション削除
void AnimationManager::Clear()
{
    m_animations.clear();
}

// 終了処理
void AnimationManager::Release()
{
    Clear();
}