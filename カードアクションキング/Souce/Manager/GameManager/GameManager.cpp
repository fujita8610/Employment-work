#include "GameManager.h"
#include "DxLib.h"

//各マネージャー
#include"../../Scene/Base/SceneManager.h"

#include "../Input/InputManager.h"
#include "../Resource/ResourceManager.h"
#include "../../UI/UIManager.h"

//カードマネージャー
#include "../../card/Manager/CardManager.h"
//CSVローダー
#include"../../card/CSV/CSVLoader.h"

GameManager& GameManager::GetInstance()
{
    static GameManager instance;
    return instance;
}

bool GameManager::Init()
{
    //ここで各Managerを初期化する

    
	//リソースマネージャー
    ResourceManager::GetInstance().Init();

	//UIマネージャー
    UIManager::GetInstance().Init();

    if (!CardManager::GetInstance().Load("Data/Z/カードリスト.csv"))
    {
        return false;
    }


    return true;
}

void GameManager::Update()
{
    //入力更新
    InputManager::GetInstance().Update();
    //シーン更新
    SceneManager::GetInstance().Update();
    //UI更新
    UIManager::GetInstance().Update();
}

void GameManager::Draw()
{
    //現在のシーン描画
    SceneManager::GetInstance().Draw();
    //UI描画
    UIManager::GetInstance().Draw();

    //デバック用
    const CardManager& manager = CardManager::GetInstance();
    DrawString(
        40,
        40,
        "Card Load Success!",
        GetColor(0, 255, 0));

    DrawFormatString(
        40,
        70,
        GetColor(255, 255, 255),
        "Card Count : %d",
        (int)manager.GetCardCount());

    const CardData* card = manager.GetCard(0);

    if (card)
    {
        DrawString(
            40,
            120,
            "First Card",
            GetColor(255, 255, 0));

        DrawFormatString(
            40,
            150,
            GetColor(255, 255, 255),
            "ID : %d",
            card->id);

        DrawFormatString(
            40,
            180,
            GetColor(255, 255, 255),
            "Name : %s",
            card->name.c_str());

        DrawFormatString(
            40,
            210,
            GetColor(255, 255, 255),
            "Cost : %d",
            card->cost);

        DrawFormatString(
            40,
            240,
            GetColor(255, 255, 255),
            "HP : %d",
            card->hp);

        DrawFormatString(
            40,
            270,
            GetColor(255, 255, 255),
            "ATK : %d",
            card->attack);
    }

}

void GameManager::Release()
{
    //各Manager終了
    SceneManager::GetInstance().Release();
    ResourceManager::GetInstance().Release();
    UIManager::GetInstance().Release();
}