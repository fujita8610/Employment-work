#pragma once

//string
#include <string>

// デッキデータ
#include "../Data/DeckData.h"

class DeckSaveManager
{
public:

    // デッキを保存
    static bool SaveDeck(
        const DeckData& deckData,
        const std::string& filePath);

    // デッキを読み込む
    static bool LoadDeck(
        DeckData& deckData,
        const std::string& filePath);
};