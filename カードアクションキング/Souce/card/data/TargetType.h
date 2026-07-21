#pragma once

// 効果対象
enum class TargetType
{
    None = 0,

    // 自分
    Self,

    // 味方1体
    Ally,

    // 敵1体
    Enemy,

    // 味方全体
    AllAllies,

    // 敵全体
    AllEnemies,

    // 指定マス
    Tile,

    // 指定した行
    Row,

    // 指定した列
    Column,

    // 盤面全体
    Board
};