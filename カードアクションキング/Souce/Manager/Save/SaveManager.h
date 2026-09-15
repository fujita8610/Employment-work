#pragma once

#include <string>

class SaveManager
{
public:

    // ファイルに文字列を書き込む
    static bool SaveText(
        const std::string& filePath,
        const std::string& data);

    // ファイルから文字列を読み込む
    static bool LoadText(
        const std::string& filePath,
        std::string& outData);
};