#pragma once

//カードデータ
#include "../../../../card/data/CardData.h"


enum class UnitOwner
{
    Player,

    Enemy
};



class Unit
{
public:
    bool Init(const CardData* card);

    void Update();
    void Draw();

    //盤面座標
    void SetBoardPosition(int x, int y);

    int GetBoardX() const;
    int GetBoardY() const;

    //Ownerの取得
    void SetOwner(UnitOwner owner);

    //Ownerの設定
    UnitOwner GetOwner() const;

    //元カード
    const CardData* GetCardData() const;

    //ステータス
    int GetHP() const;
    int GetAttack() const;

    void Damage(int value);
    void Heal(int value);
    bool IsDead() const;

    // 行動済み
    void SetActed(bool acted);
    bool HasActed() const;

private:
    const CardData* m_card = nullptr;

    UnitOwner m_owner = UnitOwner::Player;

    int m_boardX = 0;
    int m_boardY = 0;

    int m_hp = 0;
    int m_attack = 0;

    bool m_isDead = false;

    bool m_hasActed = false;
};