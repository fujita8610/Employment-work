#include "CardDetailRenderer.h"

#include "DxLib.h"
#include "../../../../card/data/CardData.h"

bool CardDetailRenderer::Init()
{
    return true;
}

void CardDetailRenderer::Update()
{
}

void CardDetailRenderer::Draw(const CardData* cardData)
{
    if (cardData == nullptr)
    {
        return;
    }

    int x = m_x;
    int y = m_y;

    int right = x + m_width;
    int bottom = y + m_height;

    int panelColor = GetColor(25, 28, 45);
    int borderColor = GetColor(190, 155, 75);
    int whiteColor = GetColor(240, 240, 240);
    int goldColor = GetColor(255, 210, 100);
    int redColor = GetColor(255, 100, 100);
    int greenColor = GetColor(100, 255, 140);

    // 背景
    DrawBox(
        x, y,
        right, bottom,
        panelColor,
        TRUE);

    // 外枠
    DrawBox(
        x, y,
        right, bottom,
        borderColor,
        FALSE);

    // 内側の枠
    DrawBox(
        x + 8, y + 8,
        right - 8, bottom - 8,
        GetColor(100, 85, 60),
        FALSE);

    // カード名
    DrawString(
        x + 20,
        y + 25,
        cardData->name.c_str(),
        goldColor);

    // カードタイプ
    const char* typeText = "UNKNOWN";

    switch (cardData->type)
    {
    case CardType::Unit:
        typeText = "UNIT";
        break;

    case CardType::Spell:
        typeText = "SPELL";
        break;

    case CardType::Trap:
        typeText = "TRAP";
        break;

    case CardType::King:
        typeText = "KING";
        break;

    default:
        break;
    }

    DrawString(
        x + 20,
        y + 65,
        typeText,
        whiteColor);

    // コスト
    DrawFormatString(
        x + 190,
        y + 65,
        goldColor,
        "COST : %d",
        cardData->cost);

    // 区切り線
    DrawLine(
        x + 15, y + 100,
        right - 15, y + 100,
        borderColor);

    // HP
    DrawFormatString(
        x + 20,
        y + 125,
        greenColor,
        "HP : %d",
        cardData->hp);

    // ATK
    DrawFormatString(
        x + 160,
        y + 125,
        redColor,
        "ATK : %d",
        cardData->attack);

    // 説明欄
    DrawString(
        x + 20,
        y + 180,
        "DESCRIPTION",
        goldColor);

    DrawLine(
        x + 15, y + 205,
        right - 15, y + 205,
        borderColor);

    DrawString(
        x + 20,
        y + 225,
        cardData->description.c_str(),
        whiteColor);
}

void CardDetailRenderer::Clear()
{
}

void CardDetailRenderer::Release()
{
    Clear();
}