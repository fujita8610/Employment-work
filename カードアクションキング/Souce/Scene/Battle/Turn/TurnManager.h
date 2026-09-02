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

    // 初期化
    bool Init(BattleManager* battleManager);

    // 更新
    void Update();

    // 戦闘開始
    void StartBattle();

    // 現在のターンを終了
    void EndCurrentTurn();

    // 終了処理
    void Release();


    //========================================
    // ターン情報
    //========================================

    // 現在のターン
    TurnType GetCurrentTurn() const;

    // 現在のターン番号
    int GetTurnCount() const;


    //========================================
    // ターン判定
    //========================================

    bool IsPlayerTurn() const;
    bool IsEnemyTurn() const;

    //========================================
    // プレイヤータイプ判定
    //========================================
    bool IsHumanTurn() const;
    bool IsAITurn() const;
    bool IsAutoTurn() const;

    //========================================
    // 操作方式
    //========================================

    // 指定プレイヤーの操作方式取得
    ControllerType GetControllerType(TurnType turn) const;


    //========================================
    // 操作方式設定
    //========================================

    void SetPlayer1Controller(ControllerType controller);
    void SetPlayer2Controller(ControllerType controller);

private:
    //ターンの切り替え
    void ChangeTurn();


private:

	// バトルマネージャー
    BattleManager* m_battleManager = nullptr;

    //ターンの取得
    PlayerTurn m_playerTurn;
    EnemyTurn m_enemyTurn;

	// 現在のターン
    TurnType m_currentTurn = TurnType::None;

	// プレイヤーの操作方式
    ControllerType m_player1Controller = ControllerType::Human;
    ControllerType m_player2Controller = ControllerType::AI;

	// ターン番号
    int m_turnCount = 0;

	// 戦闘開始フラグ
    bool m_started = false;

};