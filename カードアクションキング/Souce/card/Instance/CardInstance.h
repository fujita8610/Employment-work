#pragma once

//カードデータ
#include "../data/CardData.h"

// ゲーム中に存在するカード1枚を表すクラス
class CardInstance
{
public:

    CardInstance() = default;

    // カードデータを元に初期化
    bool Init(const CardData* cardData);

    // 元となるカードデータを取得
    const CardData* GetCardData() const;

    // カードが有効か
    bool IsValid() const;

    // ゲーム中の固有ID
    int GetInstanceID() const;

    // コスト取得
    int GetCost() const;

    // 一時的なコスト変更
    void SetCost(int cost);

    // 元のコストに戻す
    void ResetCost();

private:

    // 元となるカードデータ
    const CardData* m_cardData = nullptr;

    // ゲーム中のカード固有ID
    int m_instanceID = -1;

    // 現在のコスト
    int m_currentCost = 0;

    // 次に発行するID
    static int s_nextInstanceID;
};