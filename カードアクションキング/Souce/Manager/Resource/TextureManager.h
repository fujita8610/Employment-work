#pragma once

//string‚Æunordered_map
#include <string>
#include <unordered_map>

class TextureManager
{
public:

    bool Load(const std::string& name,
        const std::string& path);

    int Get(const std::string& name) const;

    void Release();

private:

    std::unordered_map<std::string, int> m_textures;
};