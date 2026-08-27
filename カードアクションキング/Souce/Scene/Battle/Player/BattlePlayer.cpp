#include "BattlePlayer.h"


// 初期化
bool BattlePlayer::Init(UnitOwner owner)
{
    m_owner = owner;

    // デッキ初期化
    m_deck.Init();

    // 手札初期化
    m_hand.Init();

    //セレクト中のカード
    m_selectedCardIndex = -1;

    return true;
}


// 終了処理
void BattlePlayer::Release()
{
    m_deck.Clear();
    m_hand.Clear();
    m_selectedCardIndex = -1;

}

// カードを選択
void BattlePlayer::SelectCard(size_t index)
{
    // 手札の範囲外なら選択しない
    if (index >= m_hand.GetCount())
    {
        return;
    }

    // 同じカードをクリックした場合は選択解除
    if (m_selectedCardIndex == static_cast<int>(index))
    {
        ClearSelectedCard();
        return;
    }

    m_selectedCardIndex = static_cast<int>(index);
}


// 選択解除
void BattlePlayer::ClearSelectedCard()
{
    m_selectedCardIndex = -1;
}


// 選択中のカードを取得
const CardInstance* BattlePlayer::GetSelectedCard() const
{
    if (m_selectedCardIndex < 0)
    {
        return nullptr;
    }

    return m_hand.GetCard(
        static_cast<size_t>(m_selectedCardIndex));
}


// 選択中のカード番号
int BattlePlayer::GetSelectedCardIndex() const
{
    return m_selectedCardIndex;
}

// デッキ取得
Deck& BattlePlayer::GetDeck()
{
    return m_deck;
}


// 手札取得
Hand& BattlePlayer::GetHand()
{
    return m_hand;
}


// 指定枚数カードを引く
int BattlePlayer::DrawCards(int count)
{
    int drawCount = 0;

    for (int i = 0; i < count; i++)
    {
        // 山札からカードを引く
        std::unique_ptr<CardInstance> card =
            m_deck.DrawCard();

        // 山札が空なら終了
        if (card == nullptr)
        {
            break;
        }

        // 手札へ追加
        m_hand.AddCard(std::move(card));

        drawCount++;
    }

    return drawCount;
}


// 所有者を取得
UnitOwner BattlePlayer::GetOwner() const
{
    return m_owner;
}