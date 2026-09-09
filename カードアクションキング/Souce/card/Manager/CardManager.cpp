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

    // データが空なら失敗
    if (csvData.empty())
    {
        return false;
    }

    // 1行目はヘッダーなので飛ばす
    for (size_t i = 1; i < csvData.size(); ++i)
    {
        const auto& row = csvData[i];

        // 必要な列数がない場合はスキップ
        if (row.size() < 11)
        {
            continue;
        }

        CardData card;

        // ID
        card.id = std::stoi(row[0]);

        // カード名
        card.name = row[1];

        // カードタイプ
        if (row[2] == "Unit")
        {
            card.type = CardType::Unit;
        }
        else if (row[2] == "Spell")
        {
            card.type = CardType::Spell;
        }
        else if (row[2] == "Trap")
        {
            card.type = CardType::Trap;
        }
        else if (row[2] == "King")
        {
            card.type = CardType::King;
        }
        else
        {
            card.type = CardType::None;
        }

        // コスト
        card.cost = std::stoi(row[3]);

        // HP
        card.hp = std::stoi(row[4]);

        // 攻撃力
        card.attack = std::stoi(row[5]);

        // Effects
        // ※ここはCardEffectの仕様確認後に実装

        // 画像
        card.image = row[10];

        // CardDataを登録
        m_cards.push_back(card);
    }

    return !m_cards.empty();
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

