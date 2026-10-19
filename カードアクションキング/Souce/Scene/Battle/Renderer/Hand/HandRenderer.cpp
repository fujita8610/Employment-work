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
        MV1LoadModel("Data\\3Dmodel\\cardmodel1.x");

    if (m_cardModelHandle == -1)
    {
        OutputDebugStringA(
            "HandRenderer : Card model load failed.\n");

        return false;
    }

    // モデルの大きさを設定
    MV1SetScale(
        m_cardModelHandle,
        VGet(m_cardScale, m_cardScale, m_cardScale));

    return true;
}


// 手札を描画

void HandRenderer::Draw(const Hand& hand,int selectedIndex)
{
    const size_t cardCount = hand.GetCount();

    if (cardCount == 0)
    {
        return;
    }

    const int startX = CalculateStartX(cardCount);

    // 3Dカードを手札の枚数分描画
    if (m_cardModelHandle != -1)
    {
        for (size_t i = 0; i < cardCount; i++)
        {
            // 手札の中央を基準に左右へ配置
            const float centerOffset =
                (static_cast<float>(i) -
                    (static_cast<float>(cardCount) - 1.0f) / 2.0f);

            const float worldX = centerOffset * m_cardWorldSpacing;

            // 選択中のカードは少し上へ移動
            float worldY = m_cardWorldY;

            if (selectedIndex == static_cast<int>(i))
            {
                worldY += 15.0f;
            }

            MV1SetPosition(
                m_cardModelHandle,
                VGet(worldX, worldY, m_cardWorldZ));

            MV1DrawModel(m_cardModelHandle);
        }
    }

    // 既存の2D手札UIを描画
    for (size_t i = 0; i < cardCount; i++)
    {
        const CardInstance* card = hand.GetCard(i);

        if (card == nullptr)
        {
            continue;
        }

        const int x =
            startX + static_cast<int>(i) * (m_cardWidth + m_cardSpacing);

        int y = m_startY;

        if (selectedIndex == static_cast<int>(i))
        {
            y -= 30;
        }

        // カード背景
        DrawBox(
            x, y,
            x + m_cardWidth,
            y + m_cardHeight,
            GetColor(60, 60, 80),
            TRUE);

        // 選択状態に応じて枠の色を変更
        const int borderColor =
            (selectedIndex == static_cast<int>(i))
            ? GetColor(255, 255, 0)
            : GetColor(255, 255, 255);

        DrawBox(
            x, y,
            x + m_cardWidth,
            y + m_cardHeight,
            borderColor,
            FALSE);

        const CardData* data = card->GetCardData();

        if (data == nullptr)
        {
            continue;
        }

        DrawString(
            x + 10, y + 10,
            data->name.c_str(),
            GetColor(255, 255, 255));

        DrawFormatString(
            x + 10, y + 45,
            GetColor(255, 255, 0),
            "Cost : %d",
            data->cost);

        DrawFormatString(
            x + 10, y + 75,
            GetColor(0, 255, 0),
            "HP : %d",
            data->hp);

        DrawFormatString(
            x + 10, y + 105,
            GetColor(255, 100, 100),
            "ATK : %d",
            data->attack);
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