#pragma once

class BattleManager;

// ターン処理の基底クラス
class TurnBase
{
public:

    virtual ~TurnBase() = default;

    // 初期化
    virtual bool Init(BattleManager* battleManager) = 0;

    // ターン開始
    virtual void Start() = 0;

    // 更新
    virtual void Update() = 0;

    // ターン終了
    virtual void End() = 0;

    // 終了判定
    virtual bool IsFinished() const = 0;

    // リセット
    virtual void Reset() = 0;
};