#pragma once

#include "../../Renderer/unit/UnitRenderer.h"
class Board;

class BoardRenderer
{
public:

    bool Init();

    void Draw(const Board& board);

    void Release();

private:

    int m_floorModel = -1;             // 床モデル

    int m_unitCardModel = -1;          // ユニット用カードモデル

    float m_unitModelScale = 50.0f;    // ユニットモデルの拡大率

    UnitRenderer m_unitRenderer;       // キャラクターモデル描画
};