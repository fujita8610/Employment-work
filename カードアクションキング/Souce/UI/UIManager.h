#pragma once

// UIManager.h

//vector
#include <vector>

//UIBaseÇåpè≥
class UIBase;

class UIManager
{
public:

    static UIManager& GetInstance();

    bool Init();

    void Update();

    void Draw();

    void Release();

    void AddUI(UIBase* ui);

    void RemoveUI(UIBase* ui);

    void Clear();

private:

    UIManager() = default;
    ~UIManager() = default;

    std::vector<UIBase*> m_uiList;
};