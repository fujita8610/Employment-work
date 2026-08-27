#include "TurnManager.h"

// BattleManager
#include "../BattleManager.h"

bool TurnManager::Init(BattleManager* battleManager)
{
    if (battleManager == nullptr)
    {
        return false;
    }

    m_battleManager = battleManager;

    m_playerTurn.Init(battleManager);
    m_enemyTurn.Init(battleManager);

    m_currentTurn = TurnType::None;
    m_turnCount = 0;
    m_started = false;

    return true;
}

// 戦闘開始
void TurnManager::StartBattle()
{
    if (m_started)
    {
        return;
    }

    m_started = true;

    m_turnCount = 1;

    // 最初はプレイヤーターン
    m_currentTurn = TurnType::Player;

    m_playerTurn.Start();
}

// 更新
void TurnManager::Update()
{
    if (!m_started)
    {
        return;
    }

    switch (m_currentTurn)
    {
    case TurnType::Player:

        m_playerTurn.Update();

        if (m_playerTurn.IsFinished())
        {
            ChangeTurn();
        }

        break;


    case TurnType::Enemy:

        m_enemyTurn.Update();

        if (m_enemyTurn.IsFinished())
        {
            ChangeTurn();
        }

        break;


    case TurnType::None:

        break;
    }
}

// ターン切り替え
void TurnManager::ChangeTurn()
{
    switch (m_currentTurn)
    {
    case TurnType::Player:

        // 敵ターンへ
        m_currentTurn = TurnType::Enemy;

        m_enemyTurn.Reset();
        m_enemyTurn.Start();

        break;


    case TurnType::Enemy:

        // 1ターン終了
        m_turnCount++;

        // プレイヤーターンへ
        m_currentTurn = TurnType::Player;

        m_playerTurn.Reset();
        m_playerTurn.Start();

        break;


    default:
        break;
    }
}

// 現在のターンを終了
void TurnManager::EndCurrentTurn()
{
    if (!m_started)
    {
        return;
    }

    switch (m_currentTurn)
    {
    case TurnType::Player:

        m_playerTurn.End();

        break;


    case TurnType::Enemy:

        m_enemyTurn.End();

        break;


    default:
        break;
    }
}

// 現在のターン取得
TurnType TurnManager::GetCurrentTurn() const
{
    return m_currentTurn;
}

// プレイヤーターンか
bool TurnManager::IsPlayerTurn() const
{
    return m_currentTurn == TurnType::Player;
}

// エネミーターンか
bool TurnManager::IsEnemyTurn() const
{
    return m_currentTurn == TurnType::Enemy;
}

// ターン番号
int TurnManager::GetTurnCount() const
{
    return m_turnCount;
}

// 終了処理
void TurnManager::Release()
{
    m_playerTurn.Reset();
    m_enemyTurn.Reset();

    m_battleManager = nullptr;

    m_currentTurn = TurnType::None;

    m_turnCount = 0;

    m_started = false;
}