#pragma once

#include <string>
#include <vector>

#include "CardType.h"//カードタイプ
#include "CardEffect.h"//カード効果
#include "Pattern/PatternType.h"//カードの移動パターン
#include "UnitModelType.h" //ユニットモデルの種類

struct CardData
{
    // 基本情報
    int id = 0;
    std::string name;
    std::string image;

    // カード種別
    CardType type = CardType::Unit;

    int cost = 0;	//コスト

    // ユニット用ステータス
    int hp = 0;
    int attack = 0;
    //int move = 0;      // 移動力
   // int range = 1;     // 攻撃範囲

    std::string description;	//カードの説明

    std::vector<CardEffect> effects;    // 効果

	// 攻撃パターンと移動パターン
    PatternType attackPattern = PatternType::None;
    PatternType movePattern = PatternType::None;

    // 3Dモデルの種類
    UnitModelType modelType = UnitModelType::None;
};