#include "TurnManager.h"

// BattleManager
#include "../BattleManager.h"

// 初期化
bool TurnManager::Init(BattleManager* battleManager)
{
    if (battleManager == nullptr)
    {
        return false;
    }

    m_battleManager = battleManager;

	//ターンの初期化
    m_playerTurn.Init(battleManager);
    m_enemyTurn.Init(battleManager);

	//初期状態
    m_currentTurn = TurnType::None;

    // 現在はテストとして
   // Player1 = Human
   // Player2 = AI
    m_player1Controller = ControllerType::Human;
    m_player2Controller = ControllerType::AI;

    //ターン情報
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
    //今後は先攻後攻を実装
    m_currentTurn = TurnType::Player1;

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
    case TurnType::Player1:

        m_playerTurn.Update();

        if (m_playerTurn.IsFinished())
        {
            ChangeTurn();
        }

        break;


    case TurnType::Player2:

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
    case TurnType::Player1:

        // 敵ターンへ
        m_currentTurn = TurnType::Player2;

        m_enemyTurn.Reset();
        m_enemyTurn.Start();

        break;


    case TurnType::Player2:

        // 1ターン終了
        m_turnCount++;

        // プレイヤーターンへ
        m_currentTurn = TurnType::Player1;

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
    case TurnType::Player1:

        m_playerTurn.End();

        break;


    case TurnType::Player2:

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
    return m_currentTurn == TurnType::Player1;
}

// エネミーターンか
bool TurnManager::IsEnemyTurn() const
{
    return m_currentTurn == TurnType::Player2;
}

// プレイヤー操作方式が人間か
bool TurnManager::IsHumanTurn() const
{
    return GetControllerType(m_currentTurn)
        == ControllerType::Human;
}

// プレイヤー操作方式がAIか
bool TurnManager::IsAITurn() const
{
    return GetControllerType(m_currentTurn)
        == ControllerType::AI;
}

// プレイヤー操作方式が自動か
bool TurnManager::IsAutoTurn() const
{
    return GetControllerType(m_currentTurn)
        == ControllerType::Auto;
}


// ターン番号
int TurnManager::GetTurnCount() const
{
    return m_turnCount;
}

//操作方式
ControllerType TurnManager::GetControllerType(
    TurnType turn) const
{
    switch (turn)
    {
    case TurnType::Player1:

        return m_player1Controller;


    case TurnType::Player2:

        return m_player2Controller;


    case TurnType::None:

    default:

        return ControllerType::None;
    }
}

//プレイヤー１の操作方式設定
void TurnManager::SetPlayer1Controller(
    ControllerType controller)
{
    m_player1Controller = controller;
}

//プレイヤー２の操作方式設定
void TurnManager::SetPlayer2Controller(
    ControllerType controller)
{
    m_player2Controller = controller;
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

    m_player1Controller = ControllerType::None;
    m_player2Controller = ControllerType::None;
}