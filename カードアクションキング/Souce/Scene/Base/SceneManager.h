#pragma once

#include "SceneBase.h"

class SceneManager
{
public:

    static SceneManager& GetInstance();

    bool Init();

    void Update();

    void Draw();

    void ChangeScene(SceneBase* scene);

    void Release();

private:

    SceneManager() = default;

    ~SceneManager() = default;

    SceneBase* m_currentScene = nullptr;
};