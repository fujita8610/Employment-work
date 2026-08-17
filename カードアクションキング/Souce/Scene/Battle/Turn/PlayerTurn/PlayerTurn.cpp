#include "PlayerTurn.h"

bool PlayerTurn::Init()
{
    m_started = false;
    m_finished = false;

    return true;
}

void PlayerTurn::Start()
{
    m_started = true;
    m_finished = false;
}

void PlayerTurn::Update()
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
    // プレイヤーのカード操作
    // ユニット移動
    // ユニット攻撃
    // ターン終了ボタン
}

bool PlayerTurn::IsFinished() const
{
    return m_finished;
}

void PlayerTurn::End()
{
    m_finished = true;
}