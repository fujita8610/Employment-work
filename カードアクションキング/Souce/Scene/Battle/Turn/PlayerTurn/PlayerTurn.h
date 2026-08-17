#pragma once

class PlayerTurn
{
public:

    bool Init();

    void Start();

    void Update();

    bool IsFinished() const;

    void End();

private:

    bool m_started = false;
    bool m_finished = false;
};