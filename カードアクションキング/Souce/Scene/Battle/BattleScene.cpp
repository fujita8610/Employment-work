#include "BattleScene.h"

// CardManager
#include "../../card/Manager/CardManager.h"

bool BattleScene::Init()
{
    // バトルマネージャー初期化
    if (!m_battleManager.Init())
    {
        return false;
    }

    // テスト用ユニット生成
    const CardData* card =
        CardManager::GetInstance().GetCard(0);

    if (card)
    {
        m_battleManager.CreateUnit(
            card,
            UnitOwner::Player1,
            2,
            2);
    }

    return true;
}

void BattleScene::Update()
{
    m_battleManager.Update();
}

void BattleScene::Draw()
{
    m_battleManager.Draw();
}

void BattleScene::Release()
{
    m_battleManager.Release();
}