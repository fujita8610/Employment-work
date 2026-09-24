#pragma once

#include <vector>
#include <string>

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
#include "Turn/TurnManager.h"
#include "../../Manager/Input/InputManager.h"

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

    // Player1取得
    BattlePlayer& GetPlayer1();

    // Player2取得
    BattlePlayer& GetPlayer2();

	// 現在のターンのプレイヤー取得
    BattlePlayer& GetCurrentPlayer();

	// 選択中のカードを使用する
    bool UseSelectedCard(int x, int y);

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