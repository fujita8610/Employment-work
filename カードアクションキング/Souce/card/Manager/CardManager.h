#pragma once

//stringとvector
#include <vector>
#include <string>

//cppとhのインクルード
#include "../data/CardData.h"

class CardManager
{
public:

    static CardManager& GetInstance();

    bool Load(const std::string& csvPath);

    const std::vector<CardData>& GetCards() const;

    const CardData* GetCardByID(int id) const;

    void Release();

private:

    CardManager() = default;
    ~CardManager() = default;

    std::vector<CardData> m_cards;
};