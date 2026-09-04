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
    if (!m_player1.Init(UnitOwner::Player))
    {
        return false;
    }

    // 敵プレイヤー初期化
    if (!m_player2.Init(UnitOwner::Enemy))
    {
        return false;
    }

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
    if (m_turnManager.IsPlayerTurn())
    {
        int mouseX;
        int mouseY;

        GetMousePoint(&mouseX, &mouseY);

        // 左クリックされた瞬間
        if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)
        {
            int index =
                m_handRenderer.GetClickedCardIndex(
                    m_player1.GetHand(),
                    mouseX,
                    mouseY);

            if (index >= 0)
            {
                m_player1.SelectCard(
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
    m_handRenderer.Draw(m_player1.GetHand());

    // ターンデバッグ表示
    const TurnManager& turnManager = m_turnManager;

    const char* turnText = "NONE";

    if (turnManager.IsPlayerTurn())
    {
        turnText = "PLAYER TURN";
    }
    else if (turnManager.IsEnemyTurn())
    {
        turnText = "ENEMY TURN";
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
}
// 終了処理
void BattleManager::Release()
{
    // ターンマネージャー終了
    m_turnManager.Release();

    //Renderer
    m_handRenderer.Release();

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

// プレイヤー側取得
BattlePlayer& BattleManager::GetPlayer()
{
    return m_player1;
}


// 敵側取得
BattlePlayer& BattleManager::GetEnemy()
{
    return m_player2;
}

// 現在のターンのプレイヤー取得
BattlePlayer& BattleManager::GetCurrentPlayer()
{
    return m_turnManager.IsPlayerTurn() ? m_player1 : m_player2;
}