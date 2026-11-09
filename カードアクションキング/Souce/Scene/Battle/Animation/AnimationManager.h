#pragma once

#include <vector>
#include <memory>
#include "AnimationBase.h"

class AnimationBase;

class AnimationManager
{
public:

    // 初期化
    bool Init();

    // アニメーション追加
    void AddAnimation(std::unique_ptr<AnimationBase> animation);

    // 全アニメーション更新
    void Update(float deltaTime);

    // 全アニメーション終了判定
    bool IsPlaying() const;

    // 初期化・終了処理
    void Clear();

    void Release();

private:

    // アニメーション一覧
    std::vector<std::unique_ptr<AnimationBase>> m_animations;
};