#include "Unit.h"
#include "DxLib.h"

//バトルコンフィグ
#include "../../BattleConfig.h"

// 初期化
bool Unit::Init(const CardData* card)
{
    if (card == nullptr)
    {
        return false;
    }

    m_card = card;

    // カードデータから初期ステータスを取得
    m_hp = card->hp;
    m_attack = card->attack;

    m_boardX = 0;
    m_boardY = 0;

    m_isDead = false;
    m_hasActed = false;

    return true;
}

// 更新
void Unit::Update()
{
    // 現在は処理なし
}

// 描画
void Unit::Draw()
{
    //バトルコンフィグから参照
    int drawX =
        BattleConfig::BOARD_X +
        m_boardX * BattleConfig::CELL_SIZE;

    int drawY =
        BattleConfig::BOARD_Y +
        m_boardY * BattleConfig::CELL_SIZE;


    // プレイヤーと敵で色を変える
    int color =
        (m_owner == UnitOwner::Player)
        ? GetColor(0, 150, 255)
        : GetColor(255, 80, 80);

    DrawBox(
        drawX + 16,
        drawY + 16,
        drawX + 112,
        drawY + 112,
        color,
        TRUE);

    DrawBox(
        drawX + 16,
        drawY + 16,
        drawX + 112,
        drawY + 112,
        GetColor(255, 255, 255),
        FALSE);

    if (m_card)
    {
        DrawString(
            drawX + 20,
            drawY + 20,
            m_card->name.c_str(),
            GetColor(255, 255, 255));
    }

    DrawFormatString(
        drawX + 20,
        drawY + 55,
        GetColor(0, 255, 0),
        "HP:%d",
        m_hp);

    DrawFormatString(
        drawX + 20,
        drawY + 80,
        GetColor(255, 100, 100),
        "ATK:%d",
        m_attack);
}

// 盤面座標
void Unit::SetBoardPosition(int x, int y)
{
    m_boardX = x;
    m_boardY = y;
}

int Unit::GetBoardX() const
{
    return m_boardX;
}

int Unit::GetBoardY() const
{
    return m_boardY;
}

// 所有者
void Unit::SetOwner(UnitOwner owner)
{
    m_owner = owner;
}

UnitOwner Unit::GetOwner() const
{
    return m_owner;
}

// 元カード
const CardData* Unit::GetCardData() const
{
    return m_card;
}

// ステータス取得
int Unit::GetHP() const
{
    return m_hp;
}

int Unit::GetAttack() const
{
    return m_attack;
}

// ダメージ
void Unit::Damage(int value)
{
    if (m_isDead)
    {
        return;
    }

    m_hp -= value;

    if (m_hp <= 0)
    {
        m_hp = 0;
        m_isDead = true;
    }
}

// 回復
void Unit::Heal(int value)
{
    if (m_isDead)
    {
        return;
    }

    m_hp += value;

    // 最大HPはカードデータ
    if (m_card)
    {
        if (m_hp > m_card->hp)
        {
            m_hp = m_card->hp;
        }
    }
}

// 死亡判定
bool Unit::IsDead() const
{
    return m_isDead;
}

// 行動済み
void Unit::SetActed(bool acted)
{
    m_hasActed = acted;
}

bool Unit::HasActed() const
{
    return m_hasActed;
}