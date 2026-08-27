#pragma once

#include "../TurnBase.h"


class BattleManager;

class EnemyTurn : public TurnBase
{
public:

    EnemyTurn() = default;

    // 初期化
    bool Init(BattleManager* battleManager)override;

    // ターン開始
    void Start() override;

    // 更新
    void Update() override;

    // ターン終了
    void End() override;

    // 終了済みフラグ
    bool IsFinished() const override;

    //リセット
    void Reset() override;

private:

    BattleManager* m_battleManager = nullptr;

    bool m_started = false;
    bool m_finished = false;
};