#pragma once

class AnimationBase
{
public:

	AnimationBase(); // コンストラクタ
    virtual ~AnimationBase() = default;

    // アニメーション開始
    void Start(float duration);

    // アニメーション更新
    virtual void Update(float deltaTime);

    // 終了判定
    bool IsFinished() const;

    // 再生中か
    bool IsPlaying() const;

    // 進行度取得（0.0～1.0）
    float GetProgress() const;

protected:

    // アニメーション開始時の処理
    virtual void OnStart() {}

    // アニメーション終了時の処理
    virtual void OnFinished() {}

private:

	float m_duration = 1.0f; // アニメーションの総時間（秒）

	float m_elapsedTime = 0.0f; // 経過時間（秒）

	float m_progress = 0.0f; // 進行度（0.0～1.0）

	bool m_isPlaying = false; // 再生中かどうか

	bool m_isFinished = false; // アニメーションが終了したかどうか
};