#include "BoardRenderer.h"

#include "../Board.h"
#include "../../BattleConfig.h"
#include "../Unit/Unit.h"

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

    // 盤面上のユニットを描画
    for (int y = 0;
        y < BattleConfig::BOARD_HEIGHT;
        y++)
    {
        for (int x = 0;
            x < BattleConfig::BOARD_WIDTH;
            x++)
        {
            Cell* cell =
                const_cast<Board&>(board).GetCell(x, y);

            if (cell == nullptr)
            {
                continue;
            }

            if (!cell->HasUnit())
            {
                continue;
            }

            Unit* unit =
                cell->GetUnit();

            if (unit == nullptr)
            {
                continue;
            }

            // マスの中心座標を計算
            float worldX =
                (x - BattleConfig::BOARD_WIDTH / 2.0f)
                * BattleConfig::CELL_SIZE
                + BattleConfig::CELL_SIZE / 2.0f;

            float worldZ =
                (y - BattleConfig::BOARD_HEIGHT / 2.0f)
                * BattleConfig::CELL_SIZE
                + BattleConfig::CELL_SIZE / 2.0f;

            // 仮のユニット表示
            VECTOR center =
                VGet(
                    worldX,
                    40.0f,
                    worldZ);

            VECTOR minPos =
                VGet(
                    worldX - 40.0f,
                    0.0f,
                    worldZ - 40.0f);

            VECTOR maxPos =
                VGet(
                    worldX + 40.0f,
                    80.0f,
                    worldZ + 40.0f);

            DrawCube3D(
                minPos,
                maxPos,
                GetColor(0, 200, 255),
                TRUE,
                GetColor(0, 0, 0));

            // ユニットの位置確認用
            DrawSphere3D(
                center,
                15.0f,
                8,
                GetColor(255, 255, 255),
                GetColor(255, 255, 255),
                TRUE);
        }
    }
}

void BoardRenderer::Release()
{

}