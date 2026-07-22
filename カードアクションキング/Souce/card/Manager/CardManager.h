#pragma once

//stringとvector
#include <vector>
#include <string>

//cppとhのインクルード
#include "../data/CardData.h"

class CardManager
{
public:

	// CardManagerのインスタンスを取得
    static CardManager& GetInstance();

    //初期化
    bool Load(const std::string& csvPath);

	//終了処理
    void Release();

	// カードデータの取得
    const std::vector<CardData>& GetCards() const;

    //ID検索
    const CardData* GetCardByID(int id) const;

    // 名前検索
    const CardData* GetCardByName(const std::string& name) const;

    // インデックス取得
    const CardData* GetCard(size_t index) const;
   
    // カード枚数
    size_t GetCardCount() const;

    // 読み込み済みか
    bool IsLoaded() const;

private:

    CardManager() = default;
    ~CardManager() = default;

    std::vector<CardData> m_cards;
};