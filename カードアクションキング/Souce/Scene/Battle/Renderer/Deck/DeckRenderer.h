#pragma once

#include <cstddef>

class DeckRenderer
{
public:

    // デッキ描画
    void Draw(size_t deckCount);

private:

    // デッキの画面座標
    int m_x = 1370;
    int m_y = 550;

    // カードの大きさ
    int m_width = 110;
    int m_height = 150;
};
