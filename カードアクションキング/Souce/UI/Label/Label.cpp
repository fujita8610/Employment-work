#include "Label.h"

#include "DxLib.h"

Label::Label()
{
    m_color = GetColor(255, 255, 255);

    m_fontHandle = -1;
}

void Label::Draw()
{
    if (!visible)
        return;

    if (m_fontHandle == -1)
    {
        DrawString(
            x,
            y,
            m_text.c_str(),
            m_color);
    }
    else
    {
        DrawStringToHandle(
            x,
            y,
            m_text.c_str(),
            m_color,
            m_fontHandle);
    }
}

void Label::SetText(const std::string& text)
{
    m_text = text;
}

void Label::SetColor(unsigned int color)
{
    m_color = color;
}

void Label::SetFont(int fontHandle)
{
    m_fontHandle = fontHandle;
}