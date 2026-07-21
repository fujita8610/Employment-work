#include "CardManager.h"

// CardManagerのインスタンスを取得
CardManager& CardManager::GetInstance()
{
    static CardManager instance;

    return instance;
}