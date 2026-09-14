#pragma once

#include <vector>

// デッキ
#include "../Deck/Deck.h"

// カード管理
#include "../Manager/CardManager.h"

// デッキを構築するクラス
class DeckBuilder
{
public:

    // カードIDのリストからデッキを作成
    static bool BuildDeck(
        const std::vector<int>& cardIDs,
        Deck& deck);
};