#pragma once

class Unit;

class Cell
{
public:

	// 
    Cell() = default;

    
    void SetPosition(int x, int y);

    int GetX() const;

    int GetY() const;

    bool HasUnit() const;

    Unit* GetUnit() const;

    void SetUnit(Unit* unit);

    void RemoveUnit();

private:

    int m_x = 0;
    int m_y = 0;

    Unit* m_unit = nullptr;
};