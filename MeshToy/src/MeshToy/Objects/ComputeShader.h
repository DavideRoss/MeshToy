#pragma once

#include <string>

class ComputeShader
{
public:
    ComputeShader() = default;
    ComputeShader(const std::string& InShaderName);

    // TODO: implement destructor

    void Use() const;

    void SetFloat(const std::string& ParameterName, float Value) const;
    void SetInt(const std::string& ParameterName, int Value) const;

private:
    std::string ShaderName;
    unsigned int ProgramPtr = 0;
};
