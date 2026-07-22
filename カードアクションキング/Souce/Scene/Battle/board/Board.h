#pragma once

#include "../BattleConfig.h"
#include "Cell/Cell.h"

class Board
{
public:

    bool Init();

    void Update();

    void Draw();

    Cell* GetCell(int x, int y);

private:

   // Cell m_cells[BattleConfig::BOARD_HEIGHT][BattleConfig::BOARD_WIDTH];
};