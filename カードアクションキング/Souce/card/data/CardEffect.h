#pragma once

#include "EffectType.h"
#include "TargetType.h"

// カード効果
struct CardEffect
{
    // 効果
    EffectType effectType = EffectType::None;

    // 対象
    TargetType targetType = TargetType::None;

    // 数値
    int value = 0;
};