#pragma once // Label.h 

#include "../UIBase.h"
//string
#include <string>

//UIBase‚ğŒp³
class Label : public UIBase
{
public:

    Label();

    void Draw() override;

    void SetText(const std::string& text);

    void SetColor(unsigned int color);

    void SetFont(int fontHandle);

private:

    std::string m_text;

    unsigned int m_color;

    int m_fontHandle;
};