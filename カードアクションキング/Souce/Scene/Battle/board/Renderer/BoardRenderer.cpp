#include "BoardRenderer.h"

#include "../Board.h"
#include "../../BattleConfig.h"
#include "../Unit/Unit.h"

#include "DxLib.h"
#include <string>

bool BoardRenderer::Init()
{
    // ユニット用カードモデルを読み込む
    m_unitCardModel = MV1LoadModel("Data\\3Dmodel\\cardVol1.x");

    // 読み込み失敗
    if (m_unitCardModel == -1)
    {
        OutputDebugStringA("BoardRenderer : Unit Card Model Load Failed.\n");
        return false;
    }

    // モデルのテクスチャ数を取得
    int textureNum = MV1GetTextureNum(m_unitCardModel);

    OutputDebugStringA(("Texture Num = " + std::to_string(textureNum) + "\n").c_str());

    // テクスチャ名を確認
    for (int i = 0; i < textureNum; i++)
    {
        const char* textureName =
            MV1GetTextureName(m_unitCardModel, i);

        OutputDebugStringA(
            ("Texture[" + std::to_string(i) + "] = "
                + (textureName != nullptr ? textureName : "NULL")
                + "\n").c_str());
    }

    // マテリアル数を取得
    int materialNum = MV1GetMaterialNum(m_unitCardModel);

    OutputDebugStringA(
        ("Material Num = " + std::to_string(materialNum) + "\n").c_str());

    // マテリアルが使用しているテクスチャ番号を確認
    for (int i = 0; i < materialNum; i++)
    {
        int textureIndex =
            MV1GetMaterialDifMapTexture(m_unitCardModel, i);

        OutputDebugStringA(
            ("Material[" + std::to_string(i)
                + "] Texture Index = "
                + std::to_string(textureIndex) + "\n").c_str());
    }

    // モデルの大きさ
    MV1SetScale(m_unitCardModel,
        VGet(m_unitModelScale,m_unitModelScale,m_unitModelScale));

    return true;
}

void BoardRenderer::Draw(const Board& board)
{
	//盤面の枠を描画
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

            VECTOR p2 = VGet(worldX + BattleConfig::CELL_SIZE,0,worldZ);

            VECTOR p3 = VGet(worldX + BattleConfig::CELL_SIZE,0,worldZ 
                + BattleConfig::CELL_SIZE);

            VECTOR p4 = VGet(worldX,0,worldZ + BattleConfig::CELL_SIZE);

            DrawLine3D(p1,p2,GetColor(255, 255, 255));

            DrawLine3D(p2,p3,GetColor(255, 255, 255));

            DrawLine3D(p3,p4,GetColor(255, 255, 255));

            DrawLine3D(p4,p1,GetColor(255, 255, 255));
        }
    }

    // 盤面上のユニットを描画
    for (int y = 0; y < BattleConfig::BOARD_HEIGHT;y++)
    {
        for (int x = 0; x < BattleConfig::BOARD_WIDTH;x++)
        {
            Cell* cell = const_cast<Board&>(board).GetCell(x, y);

            if (cell == nullptr)
            {
                continue;
            }

            if (!cell->HasUnit())
            {
                continue;
            }

            Unit* unit =cell->GetUnit();

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

			//3Dモデルを描画
            if (m_unitCardModel != -1)
            {
                VECTOR modelPos = VGet(worldX, 2.0f, worldZ);

                // モデルの位置
                MV1SetPosition(m_unitCardModel,modelPos);

                // モデルの回転
                // Blenderでカード面をXY平面に作成している場合は
                // X軸90度回転させて盤面に寝かせる
                MV1SetRotationXYZ(m_unitCardModel,
                    VGet(3.14159265f / 2.0f,0.0f,0.0f));

                // モデル描画
                MV1DrawModel(m_unitCardModel);
            }

            // デバック表示
            VECTOR center =VGet(worldX,40.0f,worldZ);

            VECTOR minPos =VGet(worldX - 40.0f,0.0f,worldZ - 40.0f);

            VECTOR maxPos =VGet(worldX + 40.0f,80.0f,worldZ + 40.0f);

            int debugColor;  // プレイヤーによって枠の色を変更
            if (unit->IsSelected())
            {
                // 選択中は黄色
                debugColor = GetColor(255, 220, 0);
            }
            else if (unit->GetOwner() == UnitOwner::Player1)
            {
                // プレイヤー
                debugColor = GetColor(0, 200, 255);
            }
            else
            {
                // 敵
                debugColor = GetColor(255, 80, 80);
            }

            // ワイヤーフレームで枠を表示
            DrawCube3D(minPos,maxPos, debugColor, FALSE, debugColor);

            // ユニットの位置確認用
            DrawSphere3D(center,15.0f,8,
                GetColor(255, 255, 255),GetColor(255, 255, 255),TRUE);
        }
    }
}

void BoardRenderer::Release()
{
    // ユニットモデル解放
    if (m_unitCardModel != -1)
    {
        MV1DeleteModel(m_unitCardModel);
        m_unitCardModel = -1;
    }

    // 床モデル解放
    if (m_floorModel != -1)
    {
        MV1DeleteModel(m_floorModel);
        m_floorModel = -1;
    }
}