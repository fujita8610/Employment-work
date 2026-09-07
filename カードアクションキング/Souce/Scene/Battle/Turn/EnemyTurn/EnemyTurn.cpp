#include "EnemyTurn.h"

// BattleManager
#include "../../BattleManager.h"

// BattlePlayer
#include "../../Player/BattlePlayer.h"

// 初期化
bool EnemyTurn::Init(BattleManager* battleManager)
{
    if (battleManager == nullptr)
    {
        return false;
    }

    m_battleManager = battleManager;

    Reset();

    return true;
}

// ターン開始
void EnemyTurn::Start()
{
    m_started = true;
    m_finished = false;

    // Start Phaseから開始
    ChangePhase(TurnPhase::Start);
}

// 更新
void EnemyTurn::Update()
{
    if (!m_started || m_finished)
    {
        return;
    }


    switch (m_phase)
    {
    case TurnPhase::Start:

        UpdateStartPhase();

        break;


    case TurnPhase::Draw:

        UpdateDrawPhase();

        break;


    case TurnPhase::Main:

        UpdateMainPhase();

        break;


    case TurnPhase::End:

        UpdateEndPhase();

        break;


    case TurnPhase::None:

    default:

        break;
    }
}

// ターン終了
void EnemyTurn::End()
{
    if (m_finished)
    {
        return;
    }

    // -------------------------
    // 敵ターン終了処理
    // -------------------------

    m_phase = TurnPhase::None;

    m_finished = true;
    m_started = false;
}

// 終了済みか
bool EnemyTurn::IsFinished() const
{
    return m_finished;
}

// 終了フラグをリセット
void EnemyTurn::Reset()
{
    m_phase = TurnPhase::None;

    m_started = false;
    m_finished = false;

    m_hasDrawn = false;
}

// フェーズ取得
// 必要なら後で追加
// TurnPhase EnemyTurn::GetPhase() const

// フェーズ変更
void EnemyTurn::ChangePhase(TurnPhase phase)
{
    m_phase = phase;
}

// =========================
// Start Phase
// =========================

void EnemyTurn::UpdateStartPhase()
{
    // 今後ここに
    // ・AIの行動準備
    // ・ユニット行動可能化
    // ・ターン開始効果
    // などを追加

    ChangePhase(TurnPhase::Draw);
}


// =========================
// Draw Phase
// =========================

void EnemyTurn::UpdateDrawPhase()
{
    if (m_hasDrawn)
    {
        ChangePhase(TurnPhase::Main);

        return;
    }

    // 現在のターンプレイヤーを取得
    BattlePlayer& player =
        m_battleManager->GetCurrentPlayer();

    // 1枚ドロー
    player.DrawCards(1);

    m_hasDrawn = true;

    ChangePhase(TurnPhase::Main);
}


// =========================
// Main Phase
// =========================

void EnemyTurn::UpdateMainPhase()
{
    // ここからAIを作っていく
    //
    // 例：
    // 1. 手札を確認
    // 2. 使用カードを決定
    // 3. ユニットを配置
    // 4. 移動
    // 5. 攻撃
    // 6. 行動終了

    // 現在はテストとして即終了
    ChangePhase(TurnPhase::End);
}


// =========================
// End Phase
// =========================

void EnemyTurn::UpdateEndPhase()
{
    // 今後ここに
    // ・ターン終了効果
    // ・状態異常
    // などを追加

    End();
}