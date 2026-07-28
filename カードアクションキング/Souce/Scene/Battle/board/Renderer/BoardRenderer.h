#pragma once

class Board;

class BoardRenderer
{
public:

    bool Init();

    void Draw(const Board& board);

    void Release();

private:

    // °ƒ‚ƒfƒ‹
    int m_floorModel = -1;
};