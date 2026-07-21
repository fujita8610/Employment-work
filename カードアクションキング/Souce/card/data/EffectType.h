#pragma once

// カード効果の種類
enum class EffectType
{
    None = 0,

    // ユニット召喚
    Summon,

    // ダメージ
    Damage,

    // ユニット破壊
    Destroy,

    // バフ
    Buff,

    // デバフ
    Debuff,

    // カードを引く
    Draw,

    // ユニットを移動させる
    Push
};