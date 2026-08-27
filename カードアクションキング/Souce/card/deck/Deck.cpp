#include "Deck.h"

//
#include <algorithm>
#include <random>


// デッキを初期化
void Deck::Init()
{
    Clear();
}


// カードを追加
void Deck::AddCard(std::unique_ptr<CardInstance> card)
{
    // nullptrは追加しない
    if (card == nullptr)
    {
        return;
    }

    m_cards.push_back(std::move(card));
}


// カードを1枚引く
std::unique_ptr<CardInstance> Deck::DrawCard()
{
    // デッキが空なら引けない
    if (m_cards.empty())
    {
        return nullptr;
    }

    // 一番上のカードを取得
    std::unique_ptr<CardInstance> card =
        std::move(m_cards.back());

    // デッキから削除
    m_cards.pop_back();

    // 引いたカードを返す
    return card;
}


// デッキをシャッフル
void Deck::Shuffle()
{
    // カードが1枚以下ならシャッフル不要
    if (m_cards.size() <= 1)
    {
        return;
    }

    // 乱数生成器
    std::random_device rd;
    std::mt19937 engine(rd());

    // シャッフル
    std::shuffle(
        m_cards.begin(),
        m_cards.end(),
        engine);
}


// デッキを空にする
void Deck::Clear()
{
    // unique_ptrなので自動的にCardInstanceも解放される
    m_cards.clear();
}


// 残り枚数を取得
size_t Deck::GetCount() const
{
    return m_cards.size();
}


// デッキが空か
bool Deck::IsEmpty() const
{
    return m_cards.empty();
}