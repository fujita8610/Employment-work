#include "UIBase.h"

void UIBase::SetPosition(int x, int y)
{
    this->x = x;
    this->y = y;
}

void UIBase::SetSize(int width, int height)
{
    this->width = width;
    this->height = height;
}

void UIBase::SetVisible(bool visible)
{
    this->visible = visible;
}

bool UIBase::IsVisible() const
{
    return visible;
}

bool UIBase::Contains(int mouseX, int mouseY) const
{
    return mouseX >= x &&
        mouseX <= x + width &&
        mouseY >= y &&
        mouseY <= y + height;
}

int UIBase::GetX() const
{
    return x;
}

int UIBase::GetY() const
{
    return y;
}