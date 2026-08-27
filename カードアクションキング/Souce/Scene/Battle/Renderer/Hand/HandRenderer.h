#pragma once

class Hand;

// 手札を画面に描画するクラス
class HandRenderer
{
public:

    // 初期化
    bool Init();

    // 手札を描画
    void Draw(const Hand& hand,int selectedIndex);


    // クリックされたカードのIndexを取得
   // クリックされていない場合は-1
    int GetClickedCardIndex(
        const Hand& hand,
        int mouseX,
        int mouseY) const;

    // 終了処理
    void Release();

private:

    // カードサイズ
    int m_cardWidth = 120;
    int m_cardHeight = 180;

    // カード間隔
    int m_cardSpacing = 20;

    // 描画開始位置
    int m_startY = 780;

    // カードの描画開始X座標を計算
    int CalculateStartX(size_t cardCount) const;
};