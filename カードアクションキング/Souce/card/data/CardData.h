#pragma once

#include <string>
#include <vector>

//カードタイプ
#include "CardType.h"

//カード効果
#include "CardEffect.h"

//カードの移動パターン
#include "Pattern/PatternType.h"

struct CardData
{
    // 基本情報
    int id = 0;
    std::string name;
    std::string image;

    // カード種別
    CardType type = CardType::Unit;

	//コスト
    int cost = 0;

    // ユニット用ステータス
    int hp = 0;
    int attack = 0;
    //int move = 0;      // 移動力
   // int range = 1;     // 攻撃範囲

	//カードの説明
    std::string description;

    // 効果
    std::vector<CardEffect> effects;

	// 攻撃パターンと移動パターン
    PatternType attackPattern = PatternType::None;
    PatternType movePattern = PatternType::None;
};