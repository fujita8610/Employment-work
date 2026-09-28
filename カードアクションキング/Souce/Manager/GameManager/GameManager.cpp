#include "GameManager.h"
#include "DxLib.h"

#include <vector>
#include <memory>

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
    if (!ResourceManager::GetInstance().Init())
    {
        return false;
    }

	//UIマネージャー
    if (!UIManager::GetInstance().Init())
    {
        return false;
    }

	//カードマネージャーのCSV読み込み
    if (!CardManager::GetInstance().Load(
        "Data\\Z\\カードリスト.csv"))
    {
        return false;
    }

    // シーンマネージャー初期化
    if (!SceneManager::GetInstance().Init())
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

}

void GameManager::Release()
{
    //各Manager終了
    SceneManager::GetInstance().Release();
    ResourceManager::GetInstance().Release();
    UIManager::GetInstance().Release();
}