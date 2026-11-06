#pragma once

struct CardData;

class CardDetailRenderer
{
public:
    bool Init();

    void Update();

    void Draw(const CardData* cardData);

    void Clear();

    void Release();

private:

    // パネルの位置とサイズ
    int m_x = 30;
    int m_y = 300;

    int m_width = 300;
    int m_height = 350;
};
