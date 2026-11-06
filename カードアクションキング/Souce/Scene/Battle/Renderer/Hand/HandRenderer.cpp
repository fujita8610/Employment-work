#include "HandRenderer.h"

#include "DxLib.h"

//インスタンス
#include "../../../../card/Instance/CardInstance.h"

//手札
#include "../../../../card/Hand/Hand.h"

// 初期化
bool HandRenderer::Init()
{
    // 3Dカードモデルを読み込む
    m_cardModelHandle =
        MV1LoadModel("Data\\3Dmodel\\cardVol1.x");

    if (m_cardModelHandle == -1)
    {
        OutputDebugStringA(
            "HandRenderer : Card model load failed.\n");

        return false;
    }

    // モデルの大きさを設定
    //x軸をマイナスにして左右を反転
    MV1SetScale(m_cardModelHandle,VGet(m_cardScale, m_cardScale, m_cardScale));

    // カードをY軸方向に180度回転
    // カメラ側からカードの表面が見えるようにする
    MV1SetRotationXYZ(m_cardModelHandle, VGet(0.0f, DX_PI_F*1.5, 0.0f));

    return true;
}


// 手札を描画
void HandRenderer::Draw(const Hand& hand, int selectedIndex)
{
    const size_t cardCount = hand.GetCount();

    if (cardCount == 0)
    {
        return;
    }

    const int startX = CalculateStartX(cardCount);

    // カラーパレット
	//今後はBattleConfigにまとめる
    const int darkNavy = GetColor(20, 24, 48);
    const int cardBlue = GetColor(35, 42, 75);
    const int gold = GetColor(220, 180, 90);
    const int lightGold = GetColor(255, 225, 150);
    const int white = GetColor(245, 240, 225);
    const int green = GetColor(30, 150, 80);
    const int red = GetColor(170, 55, 45);

    for (size_t i = 0; i < cardCount; i++)
    {
        const CardInstance* card = hand.GetCard(i);

        if (card == nullptr)
        {
            continue;
        }

        const CardData* data = card->GetCardData();

        if (data == nullptr)
        {
            continue;
        }

        // カード座標
        const int x = startX + static_cast<int>(i) * (m_cardWidth + m_cardSpacing);

        int y = m_startY;

        const bool selected = selectedIndex == static_cast<int>(i);

        // 選択中は少し上へ
        if (selected)
        {
            y -= 30;
        }

        const int right = x + m_cardWidth;
        const int bottom = y + m_cardHeight;

        // --------------------------------
        // 1. 影
        // --------------------------------

        DrawBox(x + 5, y + 5,right + 5, bottom + 5,GetColor(0, 0, 0),TRUE);

        // --------------------------------
        // 2. カード本体
        // --------------------------------

        DrawBox(x, y,right, bottom,darkNavy,TRUE);

        // 外側の金枠
        DrawBox(x, y,right, bottom,gold,FALSE);

        // 内側の枠
        DrawBox(x + 4, y + 4,right - 4, bottom - 4,GetColor(110, 95, 65),FALSE);

        // --------------------------------
        // 3. カード背景
        // --------------------------------

        DrawBox(x + 7, y + 7,right - 7, bottom - 7,cardBlue,TRUE);

        // 背景の内枠
        DrawBox(x + 9, y + 9,right - 9, bottom - 9,GetColor(90, 105, 145),FALSE);

        // --------------------------------
        // 4. カード名プレート
        // --------------------------------

        DrawBox(x + 5, y + 7,right - 5, y + 32,GetColor(55, 45, 40),TRUE);

        DrawBox(x + 5, y + 7,right - 5, y + 32,gold,FALSE);

        DrawString(x + 9,y + 13,data->name.c_str(),white);

        // --------------------------------
        // 5. コストバッジ
        // --------------------------------

        DrawCircle(x + 15,y + 48,12,gold, TRUE);

        DrawCircle(x + 15,y + 48,12,lightGold,FALSE);

        DrawFormatString(x + 11,y + 41,white,"%d",data->cost);

        // COST表記
        DrawString(x + 32,y + 42,"COST",lightGold);

        // --------------------------------
        // 6. カード中央の装飾
        // --------------------------------

        DrawLine(x + 10, y + 67,right - 10, y + 67,gold);

        // 中央の装飾マーク
        DrawCircle(x + m_cardWidth / 2,y + 88,13,GetColor(100, 110, 145),FALSE);

        DrawCircle(x + m_cardWidth / 2,y + 88,8,gold,FALSE);

        // --------------------------------
        // 7. HPプレート
        // --------------------------------

        const int statY = bottom - 47;

        DrawBox(
            x + 7, statY,
            x + m_cardWidth / 2, bottom - 7,
            GetColor(15, 65, 45),
            TRUE);

        DrawBox(
            x + 7, statY,
            x + m_cardWidth / 2, bottom - 7,
            green,
            FALSE);

        DrawFormatString(
            x + 12,
            statY + 9,
            GetColor(120, 255, 150),
            "HP %d",
            data->hp);

        // --------------------------------
        // 8. ATKプレート
        // --------------------------------

        DrawBox(
            x + m_cardWidth / 2, statY,
            right - 7, bottom - 7,
            GetColor(75, 25, 30),
            TRUE);

        DrawBox(
            x + m_cardWidth / 2, statY,
            right - 7, bottom - 7,
            red,FALSE);

        DrawFormatString(
            x + m_cardWidth / 2 + 5,
            statY + 9,
            GetColor(255, 130, 110),
            "ATK %d", data->attack);

        // --------------------------------
        // 9. 選択中のカード装飾
        // --------------------------------

        if (selected)
        {
            // 金色の外枠
            DrawBox(
                x - 3, y - 3,
                right + 3, bottom + 3,
                lightGold,
                FALSE);

            // さらに内側の発光風装飾
            DrawBox(
                x - 1, y - 1,
                right + 1, bottom + 1,
                gold,
                FALSE);
        }
    }
}



int HandRenderer::CalculateStartX(size_t cardCount) const
{
    if (cardCount == 0)
    {
        return 0;
    }

    // 現在の画面サイズ
    int screenWidth;
    int screenHeight;

    GetScreenState(&screenWidth, &screenHeight, nullptr);

    const int totalWidth =
        static_cast<int>(cardCount) * m_cardWidth +
        static_cast<int>(cardCount - 1) * m_cardSpacing;

    return (screenWidth - totalWidth) / 2;
}

//クリック判定
int HandRenderer::GetClickedCardIndex(
    const Hand& hand,
    int mouseX,
    int mouseY) const
{
    const size_t cardCount = hand.GetCount();

    if (cardCount == 0)
    {
        return -1;
    }

    const int startX =
        CalculateStartX(cardCount);

    for (size_t i = 0; i < cardCount; i++)
    {
        const int x =
            startX +
            static_cast<int>(i) *
            (m_cardWidth + m_cardSpacing);

        const int y = m_startY;

        // カードの範囲内か
        if (mouseX >= x &&
            mouseX <= x + m_cardWidth &&
            mouseY >= y &&
            mouseY <= y + m_cardHeight)
        {
            return static_cast<int>(i);
        }
    }

    return -1;
}

// 終了処理
void HandRenderer::Release()
{
    if (m_cardModelHandle != -1)
    {
        MV1DeleteModel(m_cardModelHandle);
        m_cardModelHandle = -1;
    }
}