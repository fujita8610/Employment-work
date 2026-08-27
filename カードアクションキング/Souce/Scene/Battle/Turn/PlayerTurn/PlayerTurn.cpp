#include "PlayerTurn.h"

//バトルマネージャー
#include "../../BattleManager.h"

//プレイヤー
#include "../../Player/BattlePlayer.h"

//初期化
bool PlayerTurn::Init(BattleManager* battleManager)
{
    if (battleManager == nullptr)
    {
        return false;
    }

    m_battleManager = battleManager;

    Reset();

    return true;
}

//ターン開始
void PlayerTurn::Start()
{
    m_started = true;
    m_finished = false;

    // =========================
   // プレイヤーターン開始処理
   // =========================

   //ターン開始フェーズから開始
    ChangePhase(TurnPhase::Start);
}

//更新
void PlayerTurn::Update()
{
    if (!m_started || m_finished)
    {
        return;
    }

    // =========================
   // プレイヤー操作
   // =========================

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

//ターン終了
void PlayerTurn::End()
{
    if (m_finished)
    {
        return;
    }

    // =========================
    // ターン終了処理
    // =========================

    m_phase = TurnPhase::None;
    m_finished = true;
    m_started = false;
}

//終了処理フラグ
bool PlayerTurn::IsFinished() const
{
    return m_finished;
}

//状態のリセット
void PlayerTurn::Reset()
{
    m_phase = TurnPhase::None;

    m_started = false;
    m_finished = false;

    m_hasDrawn = false;
}

// 現在のフェーズ取得
TurnPhase PlayerTurn::GetPhase() const
{
    return m_phase;
}

// フェーズ変更
void PlayerTurn::ChangePhase(TurnPhase phase)
{
    m_phase = phase;
}


// -------------------------
// Start Phase
// -------------------------
void PlayerTurn::UpdateStartPhase()
{
    // 今後ここに
    // ・ターン開始時効果
    // ・ユニット行動可能状態に戻す
    // ・エネルギー回復
    // などを追加

    // 次のフェーズへ
    ChangePhase(TurnPhase::Draw);
}

// -------------------------
// Draw Phase
// -------------------------
void PlayerTurn::UpdateDrawPhase()
{
    // すでにドロー済みなら次へ
    if (m_hasDrawn)
    {
        ChangePhase(TurnPhase::Main);
        return;
    }

    // BattleManagerからプレイヤーを取得
    BattlePlayer& player =
        m_battleManager->GetPlayer();

    // 1枚ドロー
    player.DrawCards(1);

    m_hasDrawn = true;
}

// -------------------------
// Main Phase
// -------------------------
void PlayerTurn::UpdateMainPhase()
{
    // 今後ここに
    // ・カード選択
    // ・カード使用
    // ・ユニット選択
    // ・移動
    // ・攻撃
    // ・ターン終了ボタン

    // 現在はプレイヤー操作待ち
}

// -------------------------
// End Phase
// -------------------------
void PlayerTurn::UpdateEndPhase()
{
    // 今後ここに
    // ・ターン終了時効果
    // ・状態異常処理

    End();
}



