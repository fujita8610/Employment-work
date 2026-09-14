#include "CardManager.h"
#include "DxLib.h"
#include<algorithm>
#include <string>

//CSV
#include "../CSV/CSVLoader.h"

// 空欄でも安全に整数へ変換する
// 空欄や数字ではない値の場合は0を返す
int ToInt(const std::string& value)
{
    if (value.empty())
    {
        return 0;
    }

    try
    {
        return std::stoi(value);
    }
    catch (...)
    {
        return 0;
    }
}

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
        OutputDebugStringA("CardManager: CSVLoaderで失敗しました。\n");
        return false;
    }

    // データが空なら失敗
    if (csvData.empty())
    {
        OutputDebugStringA("CardManager: CSVデータが空です。\n");
        return false;
    }

    // 1行目はヘッダーなので飛ばす
    for (size_t i = 1; i < csvData.size(); ++i)
    {
        const auto& row = csvData[i];

        // 必要な列数がない場合はスキップ
        if (row.size() < 11)
        {
            OutputDebugStringA("CardManager: 行データが不正です。\n");
            continue;
        }

        CardData card;

        // ID
        card.id = ToInt(row[0]);

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
        card.cost = ToInt(row[3]);

        // HP
        card.hp = ToInt(row[4]);

        // 攻撃力
        card.attack = ToInt(row[5]);

		// 攻撃パターン
        if (row[6] == "Front1")
        {
            card.attackPattern = PatternType::Front1;
        }
        else if (row[6] == "Front2")
        {
            card.attackPattern = PatternType::Front2;
        }
        else if (row[6] == "Front3")
        {
            card.attackPattern = PatternType::Front3;
        }
        else if (row[6] == "Back1")
        {
            card.attackPattern = PatternType::Back1;
        }
        else if (row[6] == "Left1")
        {
            card.attackPattern = PatternType::Left1;
        }
        else if (row[6] == "Right1")
        {
            card.attackPattern = PatternType::Right1;
        }
        else if (row[6] == "DiagonalFront1")
        {
            card.attackPattern = PatternType::DiagonalFront1;
        }
        else if (row[6] == "DiagonalBack1")
        {
            card.attackPattern = PatternType::DiagonalBack1;
        }
        else if (row[6] == "FrontAndDiagonal")
        {
            card.attackPattern = PatternType::FrontAndDiagonal;
        }
        else if (row[6] == "Around1")
        {
            card.attackPattern = PatternType::Around1;
        }
        else if (row[6] == "Cross1")
        {
            card.attackPattern = PatternType::Cross1;
        }
        else if (row[6] == "Row")
        {
            card.attackPattern = PatternType::Row;
        }
        else if (row[6] == "Column")
        {
            card.attackPattern = PatternType::Column;
        }
        else if (row[6] == "All")
        {
            card.attackPattern = PatternType::All;
        }
        else
        {
            card.attackPattern = PatternType::None;
        }

		// 移動パターン
        if (row[7] == "Front1")
        {
            card.movePattern = PatternType::Front1;
        }
        else if (row[7] == "Front2")
        {
            card.movePattern = PatternType::Front2;
        }
        else if (row[7] == "Front3")
        {
            card.movePattern = PatternType::Front3;
        }
        else if (row[7] == "Back1")
        {
            card.movePattern = PatternType::Back1;
        }
        else if (row[7] == "Left1")
        {
            card.movePattern = PatternType::Left1;
        }
        else if (row[7] == "Right1")
        {
            card.movePattern = PatternType::Right1;
        }
        else if (row[7] == "DiagonalFront1")
        {
            card.movePattern = PatternType::DiagonalFront1;
        }
        else if (row[7] == "DiagonalBack1")
        {
            card.movePattern = PatternType::DiagonalBack1;
        }
        else if (row[7] == "FrontAndDiagonal")
        {
            card.movePattern = PatternType::FrontAndDiagonal;
        }
        else if (row[7] == "Around1")
        {
            card.movePattern = PatternType::Around1;
        }
        else if (row[7] == "Cross1")
        {
            card.movePattern = PatternType::Cross1;
        }
        else if (row[7] == "Row")
        {
            card.movePattern = PatternType::Row;
        }
        else if (row[7] == "Column")
        {
            card.movePattern = PatternType::Column;
        }
        else if (row[7] == "All")
        {
            card.movePattern = PatternType::All;
        }
        else
        {
            card.movePattern = PatternType::None;
        }


        // Effects
        // ※ここはCardEffectの仕様確認後に実装

        // 画像
        card.image = row[10];

        // CardDataを登録
        m_cards.push_back(card);
    }

	// 読み込み成功したか
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

