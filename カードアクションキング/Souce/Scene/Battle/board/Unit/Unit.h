class Unit
{
public:
    bool Init(const CardData* card);

    void Update();
    void Draw();

    void SetBoardPosition(int x, int y);

    int GetBoardX() const;
    int GetBoardY() const;

    int GetHP() const;
    int GetAttack() const;

    void Damage(int value);

    bool IsDead() const;

private:
    const CardData* m_card = nullptr;

    int m_boardX = 0;
    int m_boardY = 0;

    int m_hp = 0;
    int m_attack = 0;
};