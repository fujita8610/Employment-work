#include "DeckBuilder.h"

#include <memory>

// デッキを構築
bool DeckBuilder::BuildDeck(
    const std::vector<int>& cardIDs,
    Deck& deck)
{
    // デッキを空にする
    deck.Clear();

    // カードIDが空なら失敗
    if (cardIDs.empty())
    {
        return false;
    }

    // カードIDを順番に処理
    for (int cardID : cardIDs)
    {
        // CardManagerからカードデータを取得
        const CardData* cardData =
            CardManager::GetInstance().GetCardByID(cardID);

        // 存在しないカードIDならスキップ
        if (cardData == nullptr)
        {
            continue;
        }

        // CardInstanceを作成
        std::unique_ptr<CardInstance> card =
            std::make_unique<CardInstance>();

        // CardDataを設定
        if (!card->Init(cardData))
        {
            continue;
        }

        // デッキへ追加
        deck.AddCard(std::move(card));
    }

    // 1枚以上作成できていれば成功
    return !deck.IsEmpty();
}