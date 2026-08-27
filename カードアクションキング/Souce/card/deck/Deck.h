#pragma once

#include <vector>
#include <memory>

//カードインスタンス
#include "../Instance/CardInstance.h"

// 山札を管理するクラス
class Deck
{
public:

    Deck() = default;

    // デッキを初期化
    void Init();

    // カードを追加
    void AddCard(std::unique_ptr<CardInstance> card);

    // カードを引く
    std::unique_ptr<CardInstance> DrawCard();

    // デッキをシャッフル
    void Shuffle();

    // デッキを空にする
    void Clear();

    // 残り枚数を取得
    size_t GetCount() const;

    // デッキが空か
    bool IsEmpty() const;

private:

    // 山札
    std::vector<std::unique_ptr<CardInstance>> m_cards;
};