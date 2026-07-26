#include "Board.h"

#include "DxLib.h"

//ユニット
#include "Unit/Unit.h"

//
#include "Cell/Cell.h"

bool Board::Init()
{
    // 全セルの座標を設定
    for (int y = 0; y < BattleConfig::BOARD_HEIGHT; y++)
    {
        for (int x = 0; x < BattleConfig::BOARD_WIDTH; x++)
        {
            m_cells[y][x].SetPosition(x, y);
        }
    }

    return true;
}

void Board::Update()
{
    // 今は特に処理なし
}

void Board::Draw()
{
    for (int y = 0; y < BattleConfig::BOARD_HEIGHT; y++)
    {
        for (int x = 0; x < BattleConfig::BOARD_WIDTH; x++)
        {
            int drawX = BattleConfig::BOARD_X + x * BattleConfig::CELL_SIZE;
            int drawY = BattleConfig::BOARD_Y + y * BattleConfig::CELL_SIZE;

            // マス枠
            DrawBox(
                drawX,
                drawY,
                drawX + BattleConfig::CELL_SIZE,
                drawY + BattleConfig::CELL_SIZE,
                GetColor(255, 255, 255),
                FALSE);

            // ユニットがいるなら描画
            if (m_cells[y][x].HasUnit())
            {
                m_cells[y][x].GetUnit()->Draw();
            }
        }
    }
}

Cell* Board::GetCell(int x, int y)
{
    if (!IsInside(x, y))
    {
        return nullptr;
    }

    return &m_cells[y][x];
}

bool Board::IsInside(int x, int y) const
{
    return
        x >= 0 &&
        x < BattleConfig::BOARD_WIDTH &&
        y >= 0 &&
        y < BattleConfig::BOARD_HEIGHT;
}

bool Board::PlaceUnit(Unit* unit, int x, int y)
{
    if (!IsInside(x, y))
    {
        cell->SetUnit(unit);

        unit->SetBoardPosition(x, y);

        return true;
    }

    Cell* cell = GetCell(x, y);

    if (cell->HasUnit())
    {
        return false;
    }

    cell->SetUnit(unit);

    return true;
}

bool Board::MoveUnit(int fromX, int fromY, int toX, int toY)
{
    if (!IsInside(fromX, fromY))
    {
        return false;
    }

    if (!IsInside(toX, toY))
    {
        return false;
    }

    Cell* from = GetCell(fromX, fromY);
    Cell* to = GetCell(toX, toY);

    if (!from->HasUnit())
    {
        return false;
    }

    if (to->HasUnit())
    {
        return false;
    }

    Unit* unit = from->GetUnit();

    from->RemoveUnit();
    to->SetUnit(unit);

    // Unit自身の座標も更新
    unit->SetBoardPosition(toX, toY);

    return true;
}

void Board::RemoveUnit(int x, int y)
{
    if (!IsInside(x, y))
    {
        return;
    }

    GetCell(x, y)->RemoveUnit();
}