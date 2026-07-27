#pragma once

//Vector
#include <vector>

#include "Board/Board.h"
#include "Board/Unit/Unit.h"

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

private:

    Board m_board;

    std::vector<Unit*> m_units;
};