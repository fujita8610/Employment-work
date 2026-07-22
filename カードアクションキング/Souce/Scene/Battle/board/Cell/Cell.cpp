#include "Cell.h"

//À•W‚ğİ’è
void Cell::SetPosition(int x, int y)
{
    m_x = x;
    m_y = y;
}

int Cell::GetX() const
{
    return m_x;
}

int Cell::GetY() const
{
    return m_y;
}

bool Cell::HasUnit() const
{
    return m_unit != nullptr;
}

Unit* Cell::GetUnit() const
{
    return m_unit;
}

void Cell::SetUnit(Unit* unit)
{
    m_unit = unit;
}

void Cell::RemoveUnit()
{
    m_unit = nullptr;
}