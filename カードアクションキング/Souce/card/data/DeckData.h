#pragma once

#include <vector>

// デッキのセーブデータ
// ゲーム中のCardInstanceではなく、カードIDだけを保持する
struct DeckData
{
    // デッキに入っているカードID
    std::vector<int> cardIDs;

    // データを初期化
    void Clear()
    {
        cardIDs.clear();
    }

    // デッキが空か確認
    bool IsEmpty() const
    {
        return cardIDs.empty();
    }

    // デッキ枚数を取得
    size_t GetCount() const
    {
        return cardIDs.size();
    }
};