#include "CSVLoader.h"

// CSVLoaderのCSVファイルを読み込む関数
#include <fstream>
#include <sstream>

// CSVLoaderのCSVファイルを読み込む関数
bool CSVLoader::LoadCSV(
    const std::string& filePath,
    std::vector<std::vector<std::string>>& outData)
{
	// 既存のデータをクリア
    outData.clear();

	// ファイルを開く
    std::ifstream file(filePath);

    if (!file.is_open())
    {
        return false;
    }

    // CSVファイルの各行を読み込む
    std::string line;

	// UTF-8 BOMを削除するための処理
    while (std::getline(file, line))
    {
        if (!line.empty() &&
            static_cast<unsigned char>(line[0]) == 0xEF)
        {
            line.erase(0, 3);
        }

        outData.push_back(Split(line));
    }

	// ファイルを閉じる
    file.close();

    return true;
}