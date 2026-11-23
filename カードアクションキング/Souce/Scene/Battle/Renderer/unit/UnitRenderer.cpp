#include "UnitRenderer.h"
#include "DxLib.h"

#include "../../board/Unit/Unit.h"

#include <string>

// 初期化
bool UnitRenderer::Init()
{
    // モデル登録
    // 現在はファイル未配置のため、登録失敗しても続行する

    RegisterModel(UnitModelType::Knight,"Data\\3Dmodel\\Unit\\Knight.x",
        1.0f,0.0f,0.0f,0.0f);

    RegisterModel(UnitModelType::Archer,"Data\\3Dmodel\\Unit\\Archer.x",
        1.0f,0.0f,0.0f,0.0f);

    RegisterModel(UnitModelType::Spearman,"Data\\3Dmodel\\Unit\\Spearman.x",
        1.0f,0.0f,0.0f,0.0f);

    RegisterModel(UnitModelType::King,"Data\\3Dmodel\\Unit\\King.x",
        1.0f,0.0f,0.0f,0.0f);

    return true;
}

// モデル登録
bool UnitRenderer::RegisterModel(UnitModelType type,
    const char* filePath,
    float scale,
    float rotationX,
    float rotationY,
    float rotationZ,
    float heightOffset)
{
    // モデル読み込み
    int handle = MV1LoadModel(filePath);

    if (handle == -1)
    {
        std::string message = "UnitRenderer : Model Load Failed : ";

        message += filePath;
        message += "\n";

        OutputDebugStringA(message.c_str());

        return false;
    }

    // モデル情報作成
    UnitModelInfo info;

    info.handle = handle;
    info.scale = scale;

    info.rotationX = rotationX;
    info.rotationY = rotationY;
    info.rotationZ = rotationZ;

    info.heightOffset = heightOffset;

    // 大きさ設定
    MV1SetScale(handle,VGet(scale, scale, scale));

    // モデル登録
    m_models[type] = info;

    OutputDebugStringA("UnitRenderer : Model Load Success.\n");

    return true;
}

// ユニット描画
void UnitRenderer::Draw(const Unit& unit,float worldX,float worldZ)
{
    // カードデータ取得
    const CardData* card = unit.GetCardData();

    if (card == nullptr)
    {
        return;
    }

    // 仮設定：カードIDによるモデル判定
    // 後ほどCardDataに専用のModelTypeを追加する

    UnitModelType type = UnitModelType::None;

    UnitModelType type = card->modelType;

    if (type == UnitModelType::None)
    {
        return;
    }

    // モデル検索
    auto it = m_models.find(type);

    if (it == m_models.end())
    {
        return;
    }

    UnitModelInfo& model = it->second;

    if (model.handle == -1)
    {
        return;
    }

    // モデル位置
    VECTOR position = VGet(worldX,model.heightOffset,worldZ);

    MV1SetPosition(model.handle, position);

    // 回転設定
    MV1SetRotationXYZ(model.handle,
        VGet(model.rotationX,model.rotationY,model.rotationZ));

    // 描画
    MV1DrawModel(model.handle);
}

// 解放
void UnitRenderer::Release()
{
    for (auto& model : m_models)
    {
        if (model.second.handle != -1)
        {
            MV1DeleteModel(model.second.handle);

            model.second.handle = -1;
        }
    }

    m_models.clear();
}
