#pragma once

class SceneBase
{
public:

    virtual ~SceneBase() = default;

    virtual bool Init() = 0;

    virtual void Update() = 0;

    virtual void Draw() = 0;

    virtual void Release() = 0;
};