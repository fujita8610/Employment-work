#pragma once

//unit
#include "../board/Unit/Unit.h"

// 前方宣言
class BattleManager;
class BattlePlayer;

// AIが現在何をしているか
enum class AIActionPhase
{
    None,

    // カードを選ぶ
    SelectCard,

    // カードを使う
    UseCard,

    // 操作するユニットを選ぶ
    SelectUnit,

    // ユニットを移動
    MoveUnit,

    // 攻撃するか判断
    DecideAttack,

    // 攻撃対象を選ぶ
    SelectTarget,

    // 攻撃
    Attack,

    // ターン終了
    End
};

class AIController
{
public:
    AIController() = default;

    // 初期化
    bool Init(BattleManager* battleManager, UnitOwner owner);

    // AI開始
    void Start();

    // AI更新
    void Update();

    // AI終了
    void End();

    // リセット
    void Reset();

    // 完了したか
    bool IsFinished() const;

    // 現在のAIフェーズ
    AIActionPhase GetPhase() const;

private:

	// AIが操作するプレイヤー取得
    BattlePlayer& GetAIPlayer();

    // フェーズ変更
    void ChangePhase(AIActionPhase phase);

    // 各フェーズ
    void UpdateSelectCard();
    void UpdateUseCard();
    void UpdateSelectUnit();
    void UpdateMoveUnit();
    void UpdateDecideAttack();
    void UpdateSelectTarget();
    void UpdateAttack();
    void UpdateEnd();

private:

    // バトル管理
    BattleManager* m_battleManager = nullptr;

    // AIが操作するプレイヤー
    UnitOwner m_owner = UnitOwner::Player1;

    // 現在のAIフェーズ
    AIActionPhase m_phase = AIActionPhase::None;

    // 開始済み
    bool m_started = false;

    // 完了
    bool m_finished = false;
};