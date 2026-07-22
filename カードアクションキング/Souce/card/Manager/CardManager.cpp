#include "CardManager.h"
#include<algorithm>

//CSV
#include "../CSV/CSVLoader.h"

// CardManagerのインスタンスを取得
CardManager& CardManager::GetInstance()
{
    static CardManager instance;

    return instance;
}

//カードデータの読み込み
bool CardManager::Load(const std::string& csvPath)
{
    // 以前のデータを削除
    m_cards.clear();

    // CSVデータ
    std::vector<std::vector<std::string>> csvData;

    // 読み込み失敗
    if (!CSVLoader::LoadCSV(csvPath, csvData))
    {
        return false;
    }

    // TODO:
    // CSV → CardData へ変換する処理
    //
    // 例
    //
    // for (...)
    // {
    //     CardData card;
    //
    //     card.id = ...
    //     card.name = ...
    //     ...
    //
    //     m_cards.push_back(card);
    // }

    return true;
}

//全カードデータの取得
const std::vector<CardData>& CardManager::GetCards() const
{
    return m_cards;
}

// ID検索
const CardData* CardManager::GetCardByID(int id) const
{
    for (const auto& card : m_cards)
    {
        if (card.id == id)
        {
            return &card;
        }
    }

    return nullptr;
}

// 名前検索
const CardData* CardManager::GetCardByName(const std::string& name) const
{
    for (const auto& card : m_cards)
    {
        if (card.name == name)
        {
            return &card;
        }
    }

    return nullptr;
}

// インデックス取得
const CardData* CardManager::GetCard(size_t index) const
{
    if (index >= m_cards.size())
    {
        return nullptr;
    }

    return &m_cards[index];
}

// カード枚数
size_t CardManager::GetCardCount() const
{
    return m_cards.size();
}

// 読み込み済みか
bool CardManager::IsLoaded() const
{
    return !m_cards.empty();
}

// 終了処理
void CardManager::Release()
{
    m_cards.clear();
}

