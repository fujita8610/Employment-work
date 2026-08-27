#include "CardInstance.h"

// カード固有IDのカウンター
int CardInstance::s_nextInstanceID = 0;


// カードデータを元に初期化
bool CardInstance::Init(const CardData* cardData)
{
    // カードデータが存在しない場合は失敗
    if (cardData == nullptr)
    {
        return false;
    }

    // 元のカードデータを保存
    m_cardData = cardData;

    // ゲーム中で使用する固有IDを発行
    m_instanceID = s_nextInstanceID++;

    // 初期コストはカードデータのコスト
    m_currentCost = cardData->cost;

    return true;
}


// 元となるカードデータを取得
const CardData* CardInstance::GetCardData() const
{
    return m_cardData;
}


// カードが有効か
bool CardInstance::IsValid() const
{
    return m_cardData != nullptr;
}


// ゲーム中の固有IDを取得
int CardInstance::GetInstanceID() const
{
    return m_instanceID;
}


// 現在のコストを取得
int CardInstance::GetCost() const
{
    return m_currentCost;
}


// 現在のコストを設定
void CardInstance::SetCost(int cost)
{
    // マイナスコストにならないようにする
    if (cost < 0)
    {
        cost = 0;
    }

    m_currentCost = cost;
}


// 元のコストに戻す
void CardInstance::ResetCost()
{
    if (m_cardData == nullptr)
    {
        return;
    }

    m_currentCost = m_cardData->cost;
}