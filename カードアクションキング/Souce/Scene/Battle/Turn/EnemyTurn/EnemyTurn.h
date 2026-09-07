#pragma once

#include "../TurnBase.h"
#include "../../TurnPhase/TurnPhase.h"


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

    // フェーズ変更
    void ChangePhase(TurnPhase phase);

    // 各フェーズ
    void UpdateStartPhase();
    void UpdateDrawPhase();
    void UpdateMainPhase();
    void UpdateEndPhase();

private:

    BattleManager* m_battleManager = nullptr;

    // 現在のフェーズ
    TurnPhase m_phase = TurnPhase::None;

    bool m_started = false;
    bool m_finished = false;

    // このターンにドロー済みか
    bool m_hasDrawn = false;
};