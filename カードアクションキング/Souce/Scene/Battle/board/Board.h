#pragma once

#include "../BattleConfig.h"
#include "Cell/Cell.h"

class Unit;

class Board
{
public:

    bool Init();

    void Update();

    void Draw();

	//セルの取得
    Cell* GetCell(int x, int y);

    // 範囲内か判定
    bool IsInside(int x, int y) const;

    // ユニット配置
    bool PlaceUnit(Unit* unit, int x, int y);

    // ユニット移動
    bool MoveUnit(int fromX, int fromY, int toX, int toY);

    // ユニット削除
    void RemoveUnit(int x, int y);

    // マウス位置からセル取得
    Cell* GetCellFromMouse();

    // マウス位置から座標取得
    bool GetCellIndexFromMouse(int& x, int& y);

private:

    // 5×5の盤面
   Cell m_cells[BattleConfig::BOARD_HEIGHT][BattleConfig::BOARD_WIDTH];
};