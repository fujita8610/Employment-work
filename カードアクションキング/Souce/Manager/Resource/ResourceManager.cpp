#include "ResourceManager.h"

// ResourceManagerのインスタンスを取得
ResourceManager& ResourceManager::GetInstance()
{
    static ResourceManager instance;
    return instance;
}

bool ResourceManager::Init()
{
    return true;
}

// ResourceManagerのリソースを解放
void ResourceManager::Release()
{
    m_textureManager.Release();
}

// TextureManagerのインスタンスを取得
TextureManager& ResourceManager::GetTextureManager()
{
    return m_textureManager;
}