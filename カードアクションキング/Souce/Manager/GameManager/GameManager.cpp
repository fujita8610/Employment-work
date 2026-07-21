#include "GameManager.h"

//各マネージャー
#include"../../Scene/Base/SceneManager.h"

#include "../Input/InputManager.h"
#include "../Resource/ResourceManager.h"
#include "../../UI/UIManager.h"

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
}

void GameManager::Release()
{
    //各Manager終了
    SceneManager::GetInstance().Release();
    ResourceManager::GetInstance().Release();
    UIManager::GetInstance().Release();
}