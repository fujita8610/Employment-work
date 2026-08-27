#include "EnemyTurn.h"

// BattleManager
#include "../../BattleManager.h"

bool EnemyTurn::Init(BattleManager* battleManager)
{
    if (battleManager == nullptr)
    {
        return false;
    }

    m_battleManager = battleManager;

    m_started = false;
    m_finished = false;

    return true;
}

// ターン開始
void EnemyTurn::Start()
{
    m_started = true;
    m_finished = false;

    // -------------------------
    // 敵ターン開始処理
    // -------------------------

    // 今後ここに
    // ・敵の行動可能化
    // ・AI初期化
    // ・ターン開始効果
    // などを追加する
}

// 更新
void EnemyTurn::Update()
{
    if (!m_started || m_finished)
    {
        return;
    }


    // -------------------------
    // 敵AI処理
    // -------------------------

    // 今後ここに
    // ・敵ユニット選択
    // ・移動判断
    // ・攻撃判断
    // ・カード使用
    // などを追加する

    // 現段階では外部からEnd()を呼んで終了
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

    m_finished = true;
}

// 終了済みか
bool EnemyTurn::IsFinished() const
{
    return m_finished;
}

// 終了フラグをリセット
void EnemyTurn::Reset()
{
    m_started = false;
    m_finished = false;
}