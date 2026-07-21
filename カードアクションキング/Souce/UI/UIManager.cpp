#include "UIManager.h"
#include "UIBase.h"

// UIManager.cpp

//インスタンス取得
UIManager& UIManager::GetInstance()
{
    static UIManager instance;
    return instance;
}

bool UIManager::Init()
{
    // 初期化処理
    return true;
}

void UIManager::Update()
{
	// UIの更新処理
    for (auto ui : m_uiList)
    {
        ui->Update();
    }
}

void UIManager::Draw()
{
	// UIの描画処理
    for (auto ui : m_uiList)
    {
        ui->Draw();
    }
}

void UIManager::Release()
{
	// UIの解放処理
    for (auto ui : m_uiList)
    {
        delete ui;
    }
    m_uiList.clear();
}

void UIManager::AddUI(UIBase* ui)
{
	// UIを追加する処理
    if (ui == nullptr)
        return;
    m_uiList.push_back(ui);
}

// UIを削除する処理
void UIManager::RemoveUI(UIBase* ui)
{
    //
    auto it = std::find(m_uiList.begin(), m_uiList.end(), ui);


    if (it != m_uiList.end())
    {
        m_uiList.erase(it);
    }
}

// UIをすべて削除する処理
void UIManager::Clear()
{
    for (auto ui : m_uiList)
    {
        delete ui;
    }
    m_uiList.clear();
}