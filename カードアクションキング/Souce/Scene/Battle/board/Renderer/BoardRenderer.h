#pragma once

class Board;

class BoardRenderer
{
public:

    bool Init();

    void Draw(const Board& board);

    void Release();

private:

    // 床モデル
    int m_floorModel = -1;

    int m_unitCardModel = -1;    // ユニット用カードモデル

    float m_unitModelScale = 1.0f;    // ユニットモデルの拡大率
};