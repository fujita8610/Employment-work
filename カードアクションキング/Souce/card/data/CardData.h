#pragma once

#include <string>

struct CardData
{
	//カードのID
    int id = 0;
    
    //カードの名前    
    std::string name;

	//カードの画像パス
    std::string image;

    //HP
    int hp = 0;

	//攻撃力
    int attack = 0;

	//コスト
    int cost = 0;

	//カードの説明
    std::string description;
};