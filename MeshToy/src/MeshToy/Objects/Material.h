#pragma once

#include <glm/fwd.hpp>
#include <string>

class Material
{
public:
    Material() = default;
    Material(const std::string& InMaterialName);

    // TODO: implement destructor

    void Use() const;
    
    void SetFloat(const std::string& ParameterName, float Value) const;
    void SetInt(const std::string& ParameterName, int Value) const;

    void SetVector4(const std::string& ParameterName, float X = 0, float Y = 0, float Z = 0, float W = 0) const;
    void SetVector4(const std::string& ParameterName, glm::vec4 Value) const;

    void SetMatrix4(const std::string& ParameterName, const glm::mat4& Value) const;

private:
    std::string MaterialName;

    unsigned int ProgramPtr = 0;
};
