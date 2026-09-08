#include "AIController.h"

//battleマネージャー
#include "../BattleManager.h"

//プレイヤー
#include "../Player/BattlePlayer.h"

//初期化
bool AIController::Init(
    BattleManager* battleManager,
    UnitOwner owner)
{
    if (battleManager == nullptr)
    {
        return false;
    }

    m_battleManager = battleManager;
    m_owner = owner;

    Reset();

    return true;
}

// AI開始
void AIController::Start()
{
    m_started = true;
    m_finished = false;

    ChangePhase(AIActionPhase::SelectCard);
}

//更新
void AIController::Update()
{
    if (!m_started || m_finished)
    {
        return;
    }

	//フェーズごとの処理
    switch (m_phase)
    {
    case AIActionPhase::SelectCard:
        UpdateSelectCard();
        break;

    case AIActionPhase::UseCard:
        UpdateUseCard();
        break;

    case AIActionPhase::SelectUnit:
        UpdateSelectUnit();
        break;

    case AIActionPhase::MoveUnit:
        UpdateMoveUnit();
        break;

    case AIActionPhase::DecideAttack:
        UpdateDecideAttack();
        break;

    case AIActionPhase::SelectTarget:
        UpdateSelectTarget();
        break;

    case AIActionPhase::Attack:
        UpdateAttack();
        break;

    case AIActionPhase::End:
        UpdateEnd();
        break;

    case AIActionPhase::None:
    default:
        break;
    }
}

// AI終了
void AIController::End()
{
    if (m_finished)
    {
        return;
    }

    m_phase = AIActionPhase::None;

    m_finished = true;
    m_started = false;
}

// リセット
void AIController::Reset()
{
    m_phase = AIActionPhase::None;

    m_started = false;
    m_finished = false;
}

// 完了フラグ
bool AIController::IsFinished() const
{
    return m_finished;
}

// 現在のAIフェーズ取得
AIActionPhase AIController::GetPhase() const
{
    return m_phase;
}

// フェーズ変更
void AIController::ChangePhase(AIActionPhase phase)
{
    m_phase = phase;
}