#pragma once

class GameManager
{
public:

    static GameManager& GetInstance();

    bool Init();

    void Update();

    void Draw();

    void Release();

private:

    GameManager() = default;

    ~GameManager() = default;

    GameManager(const GameManager&) = delete;
    GameManager& operator=(const GameManager&) = delete;
};