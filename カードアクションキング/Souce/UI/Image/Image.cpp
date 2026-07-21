#include "Image.h"
//Image.cpp

#include "DxLib.h"

Image::Image()
{
}

void Image::Draw()
{
    if (!visible)
        return;

    if (m_graphHandle != -1)
    {
        DrawGraph(x, y, m_graphHandle, TRUE);
    }
}

void Image::SetImage(int handle)
{
    m_graphHandle = handle;
}