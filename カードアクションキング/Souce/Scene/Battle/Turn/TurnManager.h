#pragma once

#include "TurnType.h"
#include "PlayerTurn/PlayerTurn.h"
#include "EnemyTurn/EnemyTurn.h"

#include "ControllerType.h"
class BattleManager;

class TurnManager
{
public:

    TurnManager() = default;

    //初期化
    bool Init(BattleManager* battleManager);

    //更新
    void Update();

    //終了処理
    void Release();

    //現在のターン取得
    TurnType GetCurrentTurn() const;

    //プレイヤーターン
    bool IsPlayerTurn() const;

    //エネミーターン
    bool IsEnemyTurn() const;

    //ターン終了
    void EndCurrentTurn();

    //ターン数
    int GetTurnCount() const;

    //先頭開始
    void StartBattle();

private:
    //ターンの切り替え
    void ChangeTurn();


private:

    BattleManager* m_battleManager = nullptr;

    PlayerTurn m_playerTurn;
    EnemyTurn m_enemyTurn;

    TurnType m_currentTurn = TurnType::None;

    ControllerType m_player1Controller = ControllerType::Human;
    ControllerType m_player2Controller = ControllerType::AI;

    int m_turnCount = 0;

    bool m_started = false;

};