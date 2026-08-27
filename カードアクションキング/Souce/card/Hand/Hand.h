#pragma once

#include <vector>
#include <memory>

// カードインスタンス
#include "../Instance/CardInstance.h"

// 手札を管理するクラス
class Hand
{
public:

    Hand() = default;

    // 初期化
    void Init();

    // カードを手札に追加
    void AddCard(std::unique_ptr<CardInstance> card);

    // 指定したインデックスのカードを取り出す
    std::unique_ptr<CardInstance> RemoveCard(size_t index);

    // 指定したインデックスのカードを取得（所有権は移動しない）
    const CardInstance* GetCard(size_t index) const;

    // 手札の枚数を取得
    size_t GetCount() const;

    // 手札が空か
    bool IsEmpty() const;

    // 手札を空にする
    void Clear();

private:

    // 手札のカード
    std::vector<std::unique_ptr<CardInstance>> m_cards;
};