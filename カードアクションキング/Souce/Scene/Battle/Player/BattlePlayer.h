#pragma once

#include <memory>

// カード関連
#include "../../../card/Deck/Deck.h"
#include "../../../card/Hand/Hand.h"

// 所有者
#include "../board/Unit/Unit.h"


// 戦闘中のプレイヤー情報を管理するクラス
class BattlePlayer
{
public:

    BattlePlayer() = default;

    // 初期化
    bool Init(UnitOwner owner);

    // 終了処理
    void Release();


    // -------------------------
    // カード関連
    // -------------------------

    // カードを選択
    void SelectCard(size_t index);

    // 選択解除
    void ClearSelectedCard();

    // 選択中のカード取得
    const CardInstance* GetSelectedCard() const;

    // 選択中のカード番号
    int GetSelectedCardIndex() const;

    // デッキを取得
    Deck& GetDeck();

    // 手札を取得
    Hand& GetHand();

    // カードを指定枚数引く
    int DrawCards(int count);


    // -------------------------
    // プレイヤー情報
    // -------------------------

    // 所有者を取得
    UnitOwner GetOwner() const;


private:

    // 所有者
    UnitOwner m_owner = UnitOwner::Player;

    // 選択中のカード番号
    // -1なら何も選択していない
    int m_selectedCardIndex = -1;

    // 山札
    Deck m_deck;

    // 手札
    Hand m_hand;
};