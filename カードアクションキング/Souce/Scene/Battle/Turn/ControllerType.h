#pragma once

// ターンを操作する方式
enum class ControllerType
{
    // 未設定
    None = 0,

    // 人間が操作
    Human,

    // AIが操作
    AI,

    // 自動操作
    Auto
};