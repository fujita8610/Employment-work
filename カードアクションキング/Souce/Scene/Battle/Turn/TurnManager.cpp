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

    // 操作方式に応じたターン処理を開始
    StartCurrentTurn();
}

// 更新
void TurnManager::Update()
{
    if (!m_started)
    {
        return;
    }

	// 現在の操作方式を取得
    ControllerType controller =
        GetControllerType(m_currentTurn);

	// 操作方式に応じたターン処理
    switch (controller)
    {
    case ControllerType::Human:

        m_playerTurn.Update();

        if (m_playerTurn.IsFinished())
        {
            ChangeTurn();
        }

        break;


    case ControllerType::AI:

        m_enemyTurn.Update();

        if (m_enemyTurn.IsFinished())
        {
            ChangeTurn();
        }

        break;


    case ControllerType::Auto:

        // 後でAutoTurnを実装
        break;


    case ControllerType::None:

    default:

        break;
    }
}

// ターン切り替え
void TurnManager::ChangeTurn()
{
    switch (m_currentTurn)
    {
    case TurnType::Player1:

        // Player1 → Player2
        m_currentTurn = TurnType::Player2;

        m_enemyTurn.Reset();
        m_enemyTurn.Start();

        break;


    case TurnType::Player2:

        // 1ターン終了
        m_turnCount++;

        // Player2 → Player1
        m_currentTurn = TurnType::Player1;

        m_playerTurn.Reset();
        m_playerTurn.Start();

        break;


    default:
        break;
    }
}

void TurnManager::StartCurrentTurn()
{
    // 現在の操作方式を取得
    ControllerType controller =
        GetControllerType(m_currentTurn);

    switch (controller)
    {
    case ControllerType::Human:

        // 人間操作
        m_playerTurn.Reset();
        m_playerTurn.Start();

        break;


    case ControllerType::AI:

        // AI操作
        m_enemyTurn.Reset();
        m_enemyTurn.Start();

        break;


    case ControllerType::Auto:

        // 現段階では未実装
        // 後でAutoTurnを追加する
        break;


    case ControllerType::None:

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