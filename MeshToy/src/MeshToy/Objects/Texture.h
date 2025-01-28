#pragma once

#include <string>

class Texture
{
public:
    Texture() = default;
    Texture(const std::string& InTexturePath);

    void Use() const;

private:
    std::string OriginalPath;

    unsigned int TexturePtr = 0;
    int Width, Height, ChannelsNum;
};
