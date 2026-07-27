#include "BattleManager.h"

// 初期化
bool BattleManager::Init()
{
    return m_board.Init();
}

// 更新
void BattleManager::Update()
{
    // 全ユニット更新
    for (Unit* unit : m_units)
    {
        if (unit != nullptr)
        {
            unit->Update();
        }
    }

    m_board.Update();
}

// 描画
void BattleManager::Draw()
{
    m_board.Draw();
}

// 終了処理
void BattleManager::Release()
{
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