#include "SaveManager.h"

#include <fstream>
#include <sstream>

bool SaveManager::SaveText(
    const std::string& filePath,
    const std::string& data)
{
    // ファイルを開く
    std::ofstream file(filePath);

    // 開けなかった場合
    if (!file.is_open())
    {
        return false;
    }

    // データを書き込む
    file << data;

    // ファイルを閉じる
    file.close();

    return true;
}

bool SaveManager::LoadText(
    const std::string& filePath,
    std::string& outData)
{
    // 出力データを初期化
    outData.clear();

    // ファイルを開く
    std::ifstream file(filePath);

    // 開けなかった場合
    if (!file.is_open())
    {
        return false;
    }

    // ファイル全体を読み込む
    std::stringstream buffer;
    buffer << file.rdbuf();

    outData = buffer.str();

    // ファイルを閉じる
    file.close();

    return true;
}