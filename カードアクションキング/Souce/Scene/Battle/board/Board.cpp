#include "Board.h"

#include "DxLib.h"

//ユニット
#include "Unit/Unit.h"
//
#include "Cell/Cell.h"

//Manager
#include "../../../Manager/Input/InputManager.h"

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
    //盤面外なら失敗
    if (!IsInside(x, y))
    {

        return false;
    }

    Cell* cell = GetCell(x, y);

	// すでにユニットがいる場合は失敗
    if (cell->HasUnit())
    {
        return false;
    }

    cell->SetUnit(unit);

	// Unit自身の座標も更新
    unit->SetBoardPosition(x, y);
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

// マウス位置からセル座標を取得
bool Board::GetCellIndexFromMouse(int& x, int& y)
{
    int mouseX;
    int mouseY;

    GetMousePoint(&mouseX, &mouseY);

    // マウス位置から3D空間への線分を作る
    VECTOR screenPos =
        VGet(
            static_cast<float>(mouseX),
            static_cast<float>(mouseY),
            0.0f);

    // カメラに近い位置
    VECTOR startPos =
        ConvScreenPosToWorldPos(screenPos);

    // カメラから遠い位置
    screenPos.z = 1.0f;

    VECTOR endPos =
        ConvScreenPosToWorldPos(screenPos);

    // Y=0の平面との交点を求める
    float directionY =
        endPos.y - startPos.y;

    // レイがY=0と交わらない場合
    if (directionY == 0.0f)
    {
        return false;
    }

    float t =
        -startPos.y / directionY;

    // 線分の範囲外なら無効
    if (t < 0.0f || t > 1.0f)
    {
        return false;
    }

    // Y=0との交点
    VECTOR hitPos;

    hitPos.x =
        startPos.x +
        (endPos.x - startPos.x) * t;

    hitPos.y = 0.0f;

    hitPos.z =
        startPos.z +
        (endPos.z - startPos.z) * t;

    // 盤面全体のワールドサイズ
    float boardWidth =
        BattleConfig::BOARD_WIDTH *
        BattleConfig::CELL_SIZE;

    float boardHeight =
        BattleConfig::BOARD_HEIGHT *
        BattleConfig::CELL_SIZE;

    // 盤面左上を原点に戻す
    float boardStartX =
        -boardWidth / 2.0f;

    float boardStartZ =
        -boardHeight / 2.0f;

    // セル座標へ変換
    x = static_cast<int>(
        (hitPos.x - boardStartX) /
        BattleConfig::CELL_SIZE);

    y = static_cast<int>(
        (hitPos.z - boardStartZ) /
        BattleConfig::CELL_SIZE);

    return IsInside(x, y);
}

Cell* Board::GetCellFromMouse()
{
    int x;
    int y;

    if (!GetCellIndexFromMouse(x, y))
    {
        return nullptr;
    }

    return GetCell(x, y);
}