#pragma once

#include "TextureManager.h"

class ResourceManager
{
public:

    static ResourceManager& GetInstance();

    bool Init();

    void Release();

    TextureManager& GetTextureManager();

private:

    ResourceManager() = default;
    ~ResourceManager() = default;

    TextureManager m_textureManager;
};