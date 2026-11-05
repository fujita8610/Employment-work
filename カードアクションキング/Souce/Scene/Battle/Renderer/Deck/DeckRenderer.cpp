
#include "DeckRenderer.h"

#include "DxLib.h"
#include "../../BattleConfig.h"

// デッキ描画
void DeckRenderer::Draw(size_t deckCount)
{
    // --------------------------------
    // デッキの配置設定（3Dワールド座標）
    // --------------------------------

    // 盤面の右端
    const float boardHalfWidth =
        BattleConfig::BOARD_WIDTH *
        BattleConfig::CELL_SIZE / 2.0f;

    // デッキの位置
    const float deckMinX = boardHalfWidth + 80.0f;
    const float deckMaxX = deckMinX + 110.0f;

    // 盤面手前側に配置
    const float deckMinZ = -280.0f;
    const float deckMaxZ = -130.0f;

    // デッキの厚み
    float thickness = 6.0f + deckCount * 0.8f;

    if (thickness > 35.0f)
    {
        thickness = 35.0f;
    }

    // 上面の高さ
    const float topY = thickness;

    // --------------------------------
    // 色設定
    // --------------------------------

    const int sideColor = GetColor(55, 55, 75);

    const int topColor = GetColor(35, 40, 75);

    const int edgeColor = GetColor(180, 160, 100);

    const int goldColor = GetColor(220, 190, 100);

    // --------------------------------
    // 1. デッキ本体（厚み）
    // --------------------------------

    DrawCube3D(
        VGet(deckMinX,
                0.0f,
                deckMinZ),

        VGet(deckMaxX,
                topY,
                deckMaxZ),

        sideColor,
        TRUE,
        sideColor
    );

    // --------------------------------
    // 2. デッキ上面
    // XZ平面に沿って描画
    // --------------------------------

    VECTOR p1 = VGet(deckMinX, topY + 0.5f, deckMinZ);
    VECTOR p2 = VGet(deckMaxX, topY + 0.5f, deckMinZ);
    VECTOR p3 = VGet(deckMaxX, topY + 0.5f, deckMaxZ);
    VECTOR p4 = VGet(deckMinX, topY + 0.5f, deckMaxZ);

    DrawTriangle3D(p1, p2, p3,topColor,TRUE);

    DrawTriangle3D(p1, p3, p4,topColor,TRUE);

    // --------------------------------
    // 3. カードの重なりを表現
    // 手前側面に線を描画
    // --------------------------------

    const int layerCount = 8;

    for (int i = 1; i <= layerCount; i++)
    {
        float y = thickness * i / (layerCount + 1.0f);

        DrawLine3D(
            VGet(deckMinX, y, deckMinZ),
            VGet(deckMaxX, y, deckMinZ),
            edgeColor);
    }

    // --------------------------------
    // 4. 上面の金色の枠
    // --------------------------------

    DrawLine3D(p1, p2, goldColor);
    DrawLine3D(p2, p3, goldColor);
    DrawLine3D(p3, p4, goldColor);
    DrawLine3D(p4, p1, goldColor);

    // --------------------------------
    // 5. デッキ表示文字
    // --------------------------------

    VECTOR textPos = VGet(
        (deckMinX + deckMaxX) / 2.0f,
        topY + 2.0f,
        (deckMinZ + deckMaxZ) / 2.0f);

    VECTOR screenPos = ConvWorldPosToScreenPos(textPos);

    if (screenPos.z >= 0.0f && screenPos.z <= 1.0f)
    {
        DrawString(
            static_cast<int>(screenPos.x) - 20,
            static_cast<int>(screenPos.y) - 10,
            "DECK",
            GetColor(255, 255, 255));

        DrawFormatString(
            static_cast<int>(screenPos.x) - 10,
            static_cast<int>(screenPos.y) + 15,
            GetColor(255, 220, 80),
            "%d", static_cast<int>(deckCount));
    }
}
