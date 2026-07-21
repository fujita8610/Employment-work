#pragma once // Image.h

#include "../UIBase.h"

//UIBase‚ğŒp³
class Image : public UIBase
{
public:

    Image();

    void Draw() override;

    void SetImage(int handle);

private:

    int m_graphHandle = -1;
};