#include "TextureManager.h"
#include "DxLib.h"

bool TextureManager::Load(const std::string& name,
    const std::string& path)
{
	//すでにロード済みのテクスチャ名が指定された場合は、何もせずにtrueを返す
    if (m_textures.find(name) != m_textures.end())
        return true;

    int handle = LoadGraph(path.c_str());

    if (handle == -1)
        return false;

    m_textures[name] = handle;

    return true;
}

// 指定された名前のテクスチャのハンドルを返す
int TextureManager::Get(const std::string& name) const
{
    auto itr = m_textures.find(name);

    if (itr == m_textures.end())
        return -1;

    return itr->second;
}

// すべてのテクスチャを解放する
void TextureManager::Release()
{
    for (auto& tex : m_textures)
    {
        DeleteGraph(tex.second);
    }

    m_textures.clear();
}