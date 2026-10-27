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

void HandRenderer::Draw(const Hand& hand,int selectedIndex)
{
    const size_t cardCount = hand.GetCount();

    if (cardCount == 0)
    {
        return;
    }

    const int startX = CalculateStartX(cardCount);

    // 3Dカードを描画
    if (m_cardModelHandle != -1)
    {
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

            // カードのワールド座標を計算
            const float centerOffset =
                static_cast<float>(i) -
                (static_cast<float>(cardCount) - 1.0f) / 2.0f;

            const float worldX =
                centerOffset * m_cardWorldSpacing;

            float worldY = m_cardWorldY;

            // 選択中のカードを少し上へ
            if (selectedIndex == static_cast<int>(i))
            {
                worldY += 15.0f;
            }

            // モデルを配置
            MV1SetPosition(
                m_cardModelHandle,
                VGet(worldX, worldY, m_cardWorldZ));

            // モデルを描画
            MV1DrawModel(m_cardModelHandle);
        }
    }

    // 3Dモデルの描画後に文字を重ねる
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

        // カードのワールド座標を再計算
        const float centerOffset =
            static_cast<float>(i) -
            (static_cast<float>(cardCount) - 1.0f) / 2.0f;

        const float worldX =
            centerOffset * m_cardWorldSpacing;

        float worldY = m_cardWorldY;

        if (selectedIndex == static_cast<int>(i))
        {
            worldY += 15.0f;
        }

        // 文字を表示する基準点
        // カード表面の位置に合わせて調整する
        VECTOR screenPos = ConvWorldPosToScreenPos(
            VGet(worldX, worldY + 15.0f, m_cardWorldZ));

        // カメラの後方など、投影できない位置はスキップ
        if (screenPos.z < 0.0f || screenPos.z > 1.0f)
        {
            continue;
        }

        const int textX = static_cast<int>(screenPos.x);
        const int textY = static_cast<int>(screenPos.y);

        // 名前
        // カード名：上部の白い部分
        DrawString(
            textX - 35,
            textY - 45,
            data->name.c_str(),
            GetColor(255, 255, 255));

        // HP
       // HP：右下の緑の部分
        DrawFormatString(
            textX + 5,
            textY + 45,
            GetColor(100, 255, 120),
            "HP: %d",
            data->hp);

        // 攻撃力
       // ATK：左下の赤い部分
        DrawFormatString(
            textX - 35,
            textY + 45,
            GetColor(255, 80, 60),
            "ATK: %d",
            data->attack);

    }

    // 既存の2D手札UI
    for (size_t i = 0; i < cardCount; i++)
    {
        const CardInstance* card = hand.GetCard(i);

        if (card == nullptr)
        {
            continue;
        }

        const int x =
            startX +
            static_cast<int>(i) *
            (m_cardWidth + m_cardSpacing);

        int y = m_startY;

        if (selectedIndex == static_cast<int>(i))
        {
            y -= 30;
        }

        DrawBox(
            x, y,
            x + m_cardWidth,
            y + m_cardHeight,
            GetColor(60, 60, 80),
            TRUE);

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