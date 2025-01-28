#include "Texture.h"

#include <glad/glad.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Texture::Texture(const std::string& InTexturePath)
    : OriginalPath(InTexturePath)
{
    stbi_set_flip_vertically_on_load(true);
    unsigned char* Data = stbi_load(InTexturePath.c_str(), &Width, &Height, &ChannelsNum, 0);

    if (!Data)
    {
        // TODO: logging
        return;
    }

    glGenTextures(1, &TexturePtr);
    glBindTexture(GL_TEXTURE_2D, TexturePtr);

    // TODO: values should come from some settings struct
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // TODO: check if there's an alpha channel (or only the R channel for example)
    // TODO: some options should come from texture settings
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, Width, Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, Data);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(Data);
}

void Texture::Use() const
{
    glBindTexture(GL_TEXTURE_2D, TexturePtr);
}
