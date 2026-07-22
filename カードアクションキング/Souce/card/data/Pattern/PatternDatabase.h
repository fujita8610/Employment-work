#pragma once

#include <vector>

// パターンタイプとパターンオフセットのインクルード
#include "PatternType.h"
#include "PatternOffset.h"

class PatternDatabase
{
public:

    // パターンを取得
    static const std::vector<PatternOffset>& GetPattern(PatternType type);

private:

    PatternDatabase() = default;
};