#pragma once

#include <map>

#include "../../../../card/data/UnitModelType.h"

// DxLibのモデルハンドル
using ModelHandle = int;

// モデルごとの設定
struct UnitModelInfo
{
    int handle = -1;

    float scale = 1.0f;

    // 回転角度（ラジアン）
    float rotationX = 0.0f;
    float rotationY = 0.0f;
    float rotationZ = 0.0f;

    // 台座からの高さ調整
    float heightOffset = 0.0f;
};

class Unit;

class UnitRenderer
{
public:

    // 初期化
    bool Init();

    // ユニット描画
    void Draw(const Unit& unit, float worldX, float worldZ);

    // モデル登録
    bool RegisterModel(
        UnitModelType type,
        const char* filePath,
        float scale,
        float rotationX = 0.0f,
        float rotationY = 0.0f,
        float rotationZ = 0.0f,
        float heightOffset = 0.0f
    );

    // モデル解放
    void Release();

private:

    // モデル一覧
    std::map<UnitModelType, UnitModelInfo> m_models;

};
