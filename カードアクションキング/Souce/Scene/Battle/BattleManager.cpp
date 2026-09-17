#include "DxLib.h"
#include "BattleManager.h"

// 初期化
bool BattleManager::Init()
{
    // 3Dカメラ初期化
    if (!m_camera.Init())
    {
        return false;
    }

    // 盤面初期化
    if (!m_board.Init())
    {
        return false;
    }

    // 盤面描画初期化
    if (!m_renderer.Init())
    {
        return false;
    }

    // プレイヤー初期化
    if (!m_player1.Init(UnitOwner::Player1))
    {
        return false;
    }

    //今後はデッキリストから選べるよう見する
    // 保存されたデッキを読み込む
    if (!m_player1.LoadDeck("Data\\Deck\\Player\\playersample1.txt"))
    {
        return false;
    }

    // デッキをシャッフル
    m_player1.GetDeck().Shuffle();

    // 敵プレイヤー初期化
    if (!m_player2.Init(UnitOwner::Player2))
    {
        return false;
    }

    //今後はデッキリストから選べるよう見する
  // 保存されたデッキを読み込む
    if (!m_player2.LoadDeck(
        "Data\\Deck\\Enemy\\enemysample1.txt"))
    {
        return false;
    }

    // デッキをシャッフル
    m_player2.GetDeck().Shuffle();
 

    // ターンマネージャー初期化
    if (!m_turnManager.Init(this))
    {
        return false;
    }

    // 手札描画初期化
    if (!m_handRenderer.Init())
    {
        return false;
    }

    //戦闘開始
    m_turnManager.StartBattle();
    return true;
}


// 更新
void BattleManager::Update()
{
    //カメラ更新
    m_camera.Update();

    //ターン更新
    m_turnManager.Update();

    //手札クリック処理

    // プレイヤーターンのときだけ選択可能
    if (m_turnManager.IsHumanTurn())
    {
        int mouseX;
        int mouseY;

        GetMousePoint(&mouseX, &mouseY);

        // 左クリックされた瞬間
        if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)
        {
            // 現在ターンのプレイヤーを取得
            BattlePlayer& currentPlayer =
                GetCurrentPlayer();

			// クリックされたカードのIndexを取得
            int index =
                m_handRenderer.GetClickedCardIndex(
                    currentPlayer.GetHand(),
                    mouseX,
                    mouseY);

			//カードがクリックされていた場合、選択する
            if (index >= 0)
            {
                currentPlayer.SelectCard(
                    static_cast<size_t>(index));
            }
        }
    }

    // 全ユニット更新
    for (Unit* unit : m_units)
    {
        if (unit != nullptr)
        {
            unit->Update();
        }
    }

    //盤面更新
    m_board.Update();
}

// 描画
void BattleManager::Draw()
{
    //3D盤面
    m_renderer.Draw(m_board);
    //ユニット
    m_board.Draw();
    // プレイヤーの手札
    m_handRenderer.Draw(GetCurrentPlayer().GetHand(), GetCurrentPlayer().GetSelectedCardIndex());

    //デッキ・手札のデバック
    BattlePlayer& player =
        GetCurrentPlayer();

    DrawFormatString(
        30,
        130,
        GetColor(0, 255, 255),
        "DECK : %d",
        static_cast<int>(
            player.GetDeck().GetCount()));

    DrawFormatString(
        30,
        160,
        GetColor(0, 255, 255),
        "HAND : %d",
        static_cast<int>(
            player.GetHand().GetCount()));

    // ターンデバッグ表示
    const TurnManager& turnManager = m_turnManager;

    const char* turnText = "NONE";

    if (turnManager.IsPlayerTurn())
    {
        turnText = "PLAYER１ TURN";
    }
    else if (turnManager.IsEnemyTurn())
    {
        turnText = "PLAYER２ TURN";
    }

    DrawString(
        30,
        30,
        turnText,
        GetColor(255, 255, 255));

    DrawFormatString(
        30,
        60,
        GetColor(255, 255, 255),
        "TURN : %d",
        turnManager.GetTurnCount());

	// 操作方式デバッグ表示
    const char* controllerText = "NONE";
    switch (
        turnManager.GetControllerType(
            turnManager.GetCurrentTurn()))
    {
    case ControllerType::Human:

        controllerText = "HUMAN";

        break;


    case ControllerType::AI:

        controllerText = "AI";

        break;


    case ControllerType::Auto:

        controllerText = "AUTO";

        break;


    case ControllerType::None:

    default:

        controllerText = "NONE";

        break;
    }


    DrawFormatString(
        30,
        90,
        GetColor(255, 255, 0),
        "CONTROLLER : %s",
        controllerText);
}

// 終了処理
void BattleManager::Release()
{
    // ターンマネージャー終了
    m_turnManager.Release();

    //Renderer
    m_handRenderer.Release();

    // プレイヤー終了
    m_player1.Release();
    m_player2.Release();

    // 盤面描画終了
    m_renderer.Release();

    // カメラ終了
    m_camera.Release();

    // ユニット解放
    for (Unit* unit : m_units)
    {
        delete unit;
    }

    m_units.clear();
}

// ユニット生成
Unit* BattleManager::CreateUnit(
    const CardData* card,
    UnitOwner owner,
    int x,
    int y)
{
    if (card == nullptr)
    {
        return nullptr;
    }

    Unit* unit = new Unit();

    if (!unit->Init(card))
    {
        delete unit;
        return nullptr;
    }

    unit->SetOwner(owner);
    unit->SetBoardPosition(x, y);

    if (!m_board.PlaceUnit(unit, x, y))
    {
        delete unit;
        return nullptr;
    }

    m_units.push_back(unit);

    return unit;
}

// Board取得
Board& BattleManager::GetBoard()
{
    return m_board;
}

// TurnManager取得
TurnManager& BattleManager::GetTurnManager()
{
    return m_turnManager;
}

// プレイヤー1側取得
BattlePlayer& BattleManager::GetPlayer1()
{
    return m_player1;
}

// プレイヤー2側取得
BattlePlayer& BattleManager::GetPlayer2()
{
    return m_player2;
}

// 現在のターンのプレイヤー取得
BattlePlayer& BattleManager::GetCurrentPlayer()
{
    switch (m_turnManager.GetCurrentTurn())
    {
    case TurnType::Player1:

        return m_player1;


    case TurnType::Player2:

        return m_player2;


    case TurnType::None:

    default:

        // Noneの場合もとりあえずPlayer1を返す
        return m_player1;
    }
}