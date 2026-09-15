#include "DeckSaveManager.h"

// SaveManager
#include "../../Manager/Save/SaveManager.h"

#include <sstream>

bool DeckSaveManager::SaveDeck(
    const DeckData& deckData,
    const std::string& filePath)
{
    // デッキが空の場合は保存しない
    if (deckData.IsEmpty())
    {
        return false;
    }

    std::stringstream data;

    // デッキデータの識別
    data << "[Deck]\n";

    // カードIDを書き込む
    for (size_t i = 0; i < deckData.cardIDs.size(); ++i)
    {
        data << deckData.cardIDs[i];

        // 最後のカード以外はカンマを入れる
        if (i + 1 < deckData.cardIDs.size())
        {
            data << ",";
        }
    }

    data << "\n";

    // SaveManagerに保存を任せる
    return SaveManager::SaveText(
        filePath,
        data.str());
}

bool DeckSaveManager::LoadDeck(
    DeckData& deckData,
    const std::string& filePath)
{
    // 現在のデータを消去
    deckData.Clear();

    std::string data;

    // ファイル読み込み
    if (!SaveManager::LoadText(filePath, data))
    {
        return false;
    }

    std::stringstream ss(data);
    std::string line;

    // 行を読み込む
    while (std::getline(ss, line))
    {
        // [Deck] は無視
        if (line == "[Deck]")
        {
            continue;
        }

        // カードIDをカンマ区切りで読み込む
        std::stringstream lineStream(line);
        std::string value;

        while (std::getline(lineStream, value, ','))
        {
            if (value.empty())
            {
                continue;
            }

            try
            {
                int cardID = std::stoi(value);
                deckData.cardIDs.push_back(cardID);
            }
            catch (...)
            {
                // 数値ではない場合は無視
            }
        }
    }

    return !deckData.IsEmpty();
}