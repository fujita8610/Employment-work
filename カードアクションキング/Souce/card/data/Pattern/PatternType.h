#pragma once


//マス移動パターン
// 
// マスパターン
enum class PatternType
{
    None = 0,

    // 前方
    Front1,
    Front2,
    Front3,

    // 後方
    Back1,

    // 左右
    Left1,
    Right1,

    // 斜め
    DiagonalFront1,
    DiagonalBack1,

    // 前＋斜め
    FrontAndDiagonal,

    // 周囲
    Around1,

    // 十字
    Cross1,

    // 行
    Row,

    // 列
    Column,

    // 全体
    All
};