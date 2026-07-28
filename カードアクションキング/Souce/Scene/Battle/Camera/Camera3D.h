#pragma once

#include "DxLib.h"

class Camera3D
{
public:

    Camera3D() = default;

    // 初期化
    bool Init();

    // 更新
    void Update();

    // カメラ設定をDxLibへ反映
    void Apply();

    // 終了処理
    void Release();

    // 座標設定
    void SetPosition(const VECTOR& position);

    // 注視点
    void SetTarget(const VECTOR& target);

    // Upベクトル
    void SetUp(const VECTOR& up);

    // Getter
    VECTOR GetPosition() const;
    VECTOR GetTarget() const;
    VECTOR GetUp() const;

private:

    // カメラ位置
    VECTOR m_position;

    // 注視点
    VECTOR m_target;

    // 上方向
    VECTOR m_up;
};