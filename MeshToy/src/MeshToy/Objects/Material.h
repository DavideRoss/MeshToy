#pragma once

#include <string>
#include <unordered_map>

#include <glm/fwd.hpp>

#include "Texture.h"

class Material
{
public:
    Material() = default;
    Material(const std::string& InMaterialName);

    // TODO: implement destructor

    void Use() const;
    
    void SetFloat(const std::string& ParameterName, float Value) const;
    void SetInt(const std::string& ParameterName, int Value) const;

    void SetVector2(const std::string& ParameterName, float X = 0, float Y = 0) const;
    void SetVector2(const std::string& ParameterName, glm::vec2 Value) const;

    void SetVector4(const std::string& ParameterName, float X = 0, float Y = 0, float Z = 0, float W = 0) const;
    void SetVector4(const std::string& ParameterName, glm::vec4 Value) const;

    void SetMatrix4(const std::string& ParameterName, const glm::mat4& Value) const;

    // TODO: probably not the best way to handle textures
    // TODO: correct way could be to store the uniform location along the texture number?
    void SetTexture(const std::string& ParameterName, const Texture* InTexture);

private:
    std::string MaterialName;
    unsigned int ProgramPtr = 0;
    
    std::unordered_map<std::string, const Texture*> Textures;
};
