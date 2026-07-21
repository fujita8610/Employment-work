#pragma once

// カードの種類
enum class CardType
{
    None = 0,

    // ユニットカード
    Unit,

    // スペルカード
    Spell,

    // トラップカード
    Trap,

    // キングカード
    King
};