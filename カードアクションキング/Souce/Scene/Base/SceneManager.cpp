#include "SceneManager.h"

//各シーン
#include "../Battle/BattleScene.h"

// SceneManagerのインスタンスを取得
SceneManager& SceneManager::GetInstance()
{
    static SceneManager instance;
    return instance;
}

bool SceneManager::Init()
{
    //最初に表示するシーン
    ChangeScene(new BattleScene());
    return true;
}

// 現在のシーンを更新
void SceneManager::Update()
{
    if (m_currentScene)
    {
        m_currentScene->Update();
    }
}

// 現在のシーンを描画
void SceneManager::Draw()
{
    if (m_currentScene)
    {
        m_currentScene->Draw();
    }
}

// シーンを変更する
void SceneManager::ChangeScene(SceneBase* scene)
{
    if (m_currentScene)
    {
        m_currentScene->Release();
        delete m_currentScene;
    }

    m_currentScene = scene;

    if (m_currentScene)
    {
        m_currentScene->Init();
    }
}

// 現在のシーンを解放
void SceneManager::Release()
{
    if (m_currentScene)
    {
        m_currentScene->Release();
        delete m_currentScene;
        m_currentScene = nullptr;
    }
}