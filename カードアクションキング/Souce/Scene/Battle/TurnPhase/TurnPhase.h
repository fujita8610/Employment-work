#pragma once

// ターン内の進行フェーズ
enum class TurnPhase
{
    None,

    // ターン開始処理
    Start,

    // カードを引く
    Draw,

    // カード使用・ユニット操作
    Main,

    // ターン終了処理
    End
};