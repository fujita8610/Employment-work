#pragma once

#include <vector>
#include <string>

//バトル関連
#include "BattleConfig.h"
#include "Board/Board.h"
#include "board/Renderer/BoardRenderer.h"
#include "Board/Unit/Unit.h"

//カード関連
#include "../../card/data/CardData.h"
#include "../../card/data/Pattern/PatternDatabase.h"
#include "../../card/Manager/CardManager.h"

//カメラ
#include "Camera/Camera3D.h"

//Player
#include "Player/BattlePlayer.h"

//各マネージャー
#include "Turn/TurnManager.h"       //ターン
#include "../../Manager/Input/InputManager.h"    //インプット
#include "Animation/AnimationManager.h" //アニメーション

//Renderer
#include "Renderer/Hand/HandRenderer.h"
#include "Renderer/Deck/DeckRenderer.h"
#include "Renderer/CardDetail/CardDetailRenderer.h"

//UI
class Button;

class BattleManager
{
public:

    bool Init();

    void Update();

    void Draw();

    void Release();

    // ユニット生成
    Unit* CreateUnit(const CardData* card,UnitOwner owner,int x,int y);

    Board& GetBoard();    // ボード取得

    TurnManager& GetTurnManager();    //ターンマネージャーの取得

    // Player1取得
    BattlePlayer& GetPlayer1();

    // Player2取得
    BattlePlayer& GetPlayer2();

    BattlePlayer& GetCurrentPlayer();	// 現在のターンのプレイヤー取得

    void EndCurrentTurn();    // 現在のターンを終了

    bool UseSelectedCard(int x, int y);	// 選択中のカードを使用する

    /// <summary>
    /// ユニット
    /// </summary>

    const std::vector<Unit*>& GetUnits() const;    // 盤面上のユニット一覧を取得

    void SelectUnit(Unit* unit);    // ユニット選択

    void ClearSelectedUnit();    // ユニット選択解除

    bool MoveSelectedUnit(int x, int y);    // ユニット移動

    // ターン開始時にユニットの行動状態をリセット
    void ResetUnitActions(UnitOwner owner);


/// <summary>
/// アニメーション
/// </summary>

    void StartCardDrawAnimation();  // ドローアニメーション開始


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

    TurnManager m_turnManager;   //ターン管理
    AnimationManager m_animationManager; // アニメーション管理

    //描画

    // 手札描画
    HandRenderer m_handRenderer;
	DeckRenderer m_deckRenderer; // デッキ描画
	CardDetailRenderer m_cardDetailRenderer; // カード詳細描画

    //盤面上のユニット
    std::vector<Unit*> m_units;

    // 現在選択中のユニット
    Unit* m_selectedUnit = nullptr;

	//UI関連
    // ターン終了ボタン
    Button* m_endTurnButton = nullptr;
};