#pragma once

//SceneBase
#include "../Base/SceneBase.h"

//BattleManager
#include "BattleManager.h"

class BattleScene : public SceneBase
{
public:

    bool Init() override;

    void Update() override;

    void Draw() override;

    void Release() override;

private:

    BattleManager m_battleManager;
};