#pragma once

//Vector
#include <vector>

//バトル関連
#include "Board/Board.h"
#include "board/Renderer/BoardRenderer.h"
#include "Board/Unit/Unit.h"

//カード関連
#include "../../card/data/CardData.h"
#include "../../card/Manager/CardManager.h"

//カメラ
#include "Camera/Camera3D.h"

//Player
#include "Player/BattlePlayer.h"

//各マネージャー
//ターンマネージャー
#include "Turn/TurnManager.h"

//Renderer
//Hand
#include "Renderer/Hand/HandRenderer.h"

class BattleManager
{
public:

    bool Init();

    void Update();

    void Draw();

    void Release();

    // ユニット生成
    Unit* CreateUnit(
        const CardData* card,
        UnitOwner owner,
        int x,
        int y);

    // ボード取得
    Board& GetBoard();

    //ターンマネージャーの取得
    TurnManager& GetTurnManager();

    // プレイヤー側取得
    BattlePlayer& GetPlayer();

    // エネミー側取得
    BattlePlayer& GetEnemy();

	// 現在のターンのプレイヤー取得
    BattlePlayer& GetCurrentPlayer();

private:

    // プレイヤー側
    BattlePlayer m_player1;

    // player２側
    BattlePlayer m_player2;

    //カメラ
    Camera3D m_camera;

    //盤面描画
    BoardRenderer m_renderer;
    //盤面
    Board m_board;

    //ターン管理
    TurnManager m_turnManager;

    //描画

    // 手札描画
    HandRenderer m_handRenderer;

    //盤面上のユニット
    std::vector<Unit*> m_units;
};