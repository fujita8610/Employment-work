#include "PatternDatabase.h"

const std::vector<PatternOffset>& PatternDatabase::GetPattern(PatternType type)
{
    static const std::vector<PatternOffset> none = {};

    static const std::vector<PatternOffset> front1 =
    {
		// 前方1マス
        { 0, -1 }
    };

    static const std::vector<PatternOffset> front2 =
    {
		// 前方2マス
        { 0, -1 },
        { 0, -2 }
    };

    static const std::vector<PatternOffset> front3 =
    {
		// 前方3マス
        { 0, -1 },
        { 0, -2 },
        { 0, -3 }
    };

    static const std::vector<PatternOffset> diagonalFront1 =
    {
        // 前方斜め1マス
        { -1, -1 },
        {  1, -1 }
    };

    static const std::vector<PatternOffset> frontAndDiagonal =
    {
		// 前方1マスと斜め前方1マス
        {  0, -1 },
        { -1, -1 },
        {  1, -1 }
    };

    static const std::vector<PatternOffset> around1 =
    {
		// 周囲1マス
        { -1, -1 }, { 0, -1 }, { 1, -1 },
        { -1,  0 },             { 1,  0 },
        { -1,  1 }, { 0,  1 }, { 1,  1 }
    };

    switch (type)
    {
    case PatternType::Front1:
        return front1;

    case PatternType::Front2:
        return front2;

    case PatternType::Front3:
        return front3;

    case PatternType::DiagonalFront1:
        return diagonalFront1;

    case PatternType::FrontAndDiagonal:
        return frontAndDiagonal;

    case PatternType::Around1:
        return around1;

    default:
        return none;
    }
}