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

    // 読み込み確認
    if (m_unitCardModel == -1)
    {
        OutputDebugStringA("BoardRenderer : Unit Card Model Load Failed.\n");
        return false;
    }

    OutputDebugStringA("BoardRenderer : Unit Card Model Load Success.\n");

    // モデルのテクスチャ数を取得
    int textureNum = MV1GetTextureNum(m_unitCardModel);

    OutputDebugStringA(("Texture Num = " + std::to_string(textureNum) + "\n").c_str());

    // モデルの大きさ
    MV1SetScale(m_unitCardModel,
        VGet(m_unitModelScale,m_unitModelScale,m_unitModelScale));

    int meshNum = MV1GetMeshNum(m_unitCardModel);    // モデルのメッシュ数を取得

    char debugText[256];    // メッシュ数を出力

    sprintf_s(debugText,"Model Mesh Num : %d\n",meshNum);

    OutputDebugStringA(debugText);

    // 各メッシュの大きさを確認
    for (int i = 0; i < meshNum; i++)
    {
        VECTOR minPos = MV1GetMeshMinPosition(m_unitCardModel, i);
        VECTOR maxPos = MV1GetMeshMaxPosition(m_unitCardModel, i);

        sprintf_s(debugText,"Mesh %d : X %.3f Y %.3f Z %.3f\n",
            i,maxPos.x - minPos.x,maxPos.y - minPos.y,maxPos.z - minPos.z);

        OutputDebugStringA(debugText);
    }

    // キャラクターモデル描画システムの初期化
    m_unitRenderer.Init();

    return true;
}

void BoardRenderer::Draw(const Board& board)
{
    static bool firstDraw = true;
	if (firstDraw) // 初回描画時にデバッグ出力
    {
        OutputDebugStringA("BoardRenderer : Draw Called.\n");
        firstDraw = false;
    }

	int unitCount = 0; // 盤面上のユニット数をカウント
    for (int y = 0; y < BattleConfig::BOARD_HEIGHT; y++)
    {
        for (int x = 0; x < BattleConfig::BOARD_WIDTH; x++)
        {
            Cell* cell = const_cast<Board&>(board).GetCell(x, y);

            if (cell != nullptr && cell->HasUnit())
            {
                unitCount++;
            }
        }
    }

	char debugText[128]; // デバッグ用の文字列バッファ

    sprintf_s(debugText,"BoardRenderer : Unit Count = %d\n",unitCount);
    OutputDebugStringA(debugText);


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

                MV1SetPosition(m_unitCardModel, modelPos);

                MV1SetRotationXYZ(m_unitCardModel,
                    VGet(0.0f, 3.14159265f * 1.5f, 0.0f));

                MV1DrawModel(m_unitCardModel); //
            }

            // キャラクター配置用の仮ボックス
            {
                // キャラクターの3Dモデルを描画
                m_unitRenderer.Draw(*unit, worldX, worldZ);

                // ボックスの大きさ
                float boxHalfWidth = 25.0f;
                float boxHeight = 60.0f;

                // ボックスの位置
                VECTOR boxMin =
                    VGet(worldX - boxHalfWidth,5.0f,worldZ - boxHalfWidth);

                VECTOR boxMax =
                    VGet(worldX + boxHalfWidth,boxHeight,worldZ + boxHalfWidth);

                // 所有者によって色を変更
                int boxColor;

                if (unit->GetOwner() == UnitOwner::Player1)
                {
                    boxColor = GetColor(0, 200, 255);
                }
                else
                {
                    boxColor = GetColor(255, 80, 80);
                }

                // ワイヤーフレームのボックスを描画
                DrawCube3D(boxMin,boxMax,boxColor,FALSE,boxColor);
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

    // キャラクターモデル描画システムの解放
    m_unitRenderer.Release();
}