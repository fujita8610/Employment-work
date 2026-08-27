#pragma once

#include "../TurnBase.h"
#include "../../TurnPhase/TurnPhase.h"

class BattleManager;

class PlayerTurn : public TurnBase
{
public:

    //初期化
    bool Init(BattleManager* battleManager)override;

    //ターン開始
    void Start()override;

    //更新
    void Update()override;

    //ターン終了
    void End()override;

    //終了済み
    bool IsFinished() const override;

    //状態のリセット
    void Reset()override;


private:

    // フェーズ変更
    void ChangePhase(TurnPhase phase);

    // 各フェーズ処理
    void UpdateStartPhase();
    void UpdateDrawPhase();
    void UpdateMainPhase();
    void UpdateEndPhase();



private:

    //バトルマネージャー
    BattleManager* m_battleManager = nullptr;

    //ターンフェーズ
    TurnPhase m_phase = TurnPhase::None;

    bool m_started = false;
    bool m_finished = false;

    // このターンにドロー済みか
    bool m_hasDrawn = false;

};