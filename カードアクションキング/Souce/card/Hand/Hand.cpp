#include "Hand.h"


// 手札を初期化
void Hand::Init()
{
    Clear();
}


// カードを手札に追加
void Hand::AddCard(std::unique_ptr<CardInstance> card)
{
    // nullptrは追加しない
    if (card == nullptr)
    {
        return;
    }

    // 所有権を手札へ移動
    m_cards.push_back(std::move(card));
}


// 指定したカードを手札から取り出す
std::unique_ptr<CardInstance> Hand::RemoveCard(size_t index)
{
    // 範囲外の場合は取得できない
    if (index >= m_cards.size())
    {
        return nullptr;
    }

    // カードの所有権を取得
    std::unique_ptr<CardInstance> card =
        std::move(m_cards[index]);

    // 手札から削除
    m_cards.erase(m_cards.begin() + index);

    // 取り出したカードを返す
    return card;
}


// 指定したカードを取得
const CardInstance* Hand::GetCard(size_t index) const
{
    // 範囲外の場合
    if (index >= m_cards.size())
    {
        return nullptr;
    }

    // 所有権は渡さず、参照だけ返す
    return m_cards[index].get();
}


// 手札の枚数を取得
size_t Hand::GetCount() const
{
    return m_cards.size();
}


// 手札が空か
bool Hand::IsEmpty() const
{
    return m_cards.empty();
}


// 手札を空にする
void Hand::Clear()
{
    // unique_ptrがCardInstanceを自動解放
    m_cards.clear();
}