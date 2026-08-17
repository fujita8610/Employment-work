#include "EnemyTurn.h"

bool EnemyTurn::Init()
{
    m_started = false;
    m_finished = false;

    return true;
}

void EnemyTurn::Start()
{
    m_started = true;
    m_finished = false;
}

void EnemyTurn::Update()
{
    if (!m_started)
    {
        return;
    }

    if (m_finished)
    {
        return;
    }

    // TODO:
    // 敵AI
    // 敵ユニット移動
    // 敵ユニット攻撃
    // 敵ターン終了
}

bool EnemyTurn::IsFinished() const
{
    return m_finished;
}

void EnemyTurn::End()
{
    m_finished = true;
}