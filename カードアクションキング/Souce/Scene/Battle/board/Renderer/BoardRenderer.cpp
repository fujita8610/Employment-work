#include "BoardRenderer.h"

#include "../Board.h"
#include "../../BattleConfig.h"

#include "DxLib.h"

bool BoardRenderer::Init()
{
    return true;
}

void BoardRenderer::Draw(const Board& board)
{
    for (int y = 0; y < BattleConfig::BOARD_HEIGHT; y++)
    {
        for (int x = 0; x < BattleConfig::BOARD_WIDTH; x++)
        {
            float worldX =
                (x - BattleConfig::BOARD_WIDTH / 2.0f)
                * BattleConfig::CELL_SIZE;

            float worldZ =
                (y - BattleConfig::BOARD_HEIGHT / 2.0f)
                * BattleConfig::CELL_SIZE;

            VECTOR p1 = VGet(worldX, 0, worldZ);

            VECTOR p2 = VGet(
                worldX + BattleConfig::CELL_SIZE,
                0,
                worldZ);

            VECTOR p3 = VGet(
                worldX + BattleConfig::CELL_SIZE,
                0,
                worldZ + BattleConfig::CELL_SIZE);

            VECTOR p4 = VGet(
                worldX,
                0,
                worldZ + BattleConfig::CELL_SIZE);

            DrawLine3D(
                p1,
                p2,
                GetColor(255, 255, 255));

            DrawLine3D(
                p2,
                p3,
                GetColor(255, 255, 255));

            DrawLine3D(
                p3,
                p4,
                GetColor(255, 255, 255));

            DrawLine3D(
                p4,
                p1,
                GetColor(255, 255, 255));
        }
    }
}

void BoardRenderer::Release()
{

}