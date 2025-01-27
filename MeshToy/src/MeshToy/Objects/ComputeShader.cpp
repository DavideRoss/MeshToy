#include "ComputeShader.h"

#include <format>
#include <iostream>

#include "MeshToy/Utils/ShaderCompiler.h"

ComputeShader::ComputeShader(const std::string& InShaderName)
    :ShaderName(InShaderName)
{
    std::string Source;
    if (!ShaderCompiler::OpenFile(std::format("shaders/compute/{}.glsl", InShaderName), Source))
    {
        std::cerr << std::format("Cannot open compute shader \"{}\'!\n", InShaderName);
        return;
    }

    std::string Error;
    unsigned int ShaderPtr;
    if (!ShaderCompiler::CompileShader(GL_COMPUTE_SHADER, Source, ShaderPtr, Error))
    {
        std::cerr << "Cannot compile compute shader:\n" << Error << '\n';
        return;
    }

    ProgramPtr = glCreateProgram();
    glAttachShader(ProgramPtr, ShaderPtr);
    glLinkProgram(ProgramPtr);

    int Success;
    glGetProgramiv(ProgramPtr, GL_LINK_STATUS, &Success);
    if (!Success)
    {
        char Log[512];
        glGetProgramInfoLog(ProgramPtr, 512, nullptr, Log);
        std::cerr << "Cannot link compute shader material " << InShaderName << ":\n" << Log << '\n';
        return;
    }

    glDeleteShader(ShaderPtr);
}

void ComputeShader::Use() const
{
    glUseProgram(ProgramPtr);
}

void ComputeShader::SetFloat(const std::string& ParameterName, float Value) const
{
    glUniform1f(glGetUniformLocation(ProgramPtr, ParameterName.c_str()), Value);
}

void ComputeShader::SetInt(const std::string& ParameterName, int Value) const
{
    glUniform1i(glGetUniformLocation(ProgramPtr, ParameterName.c_str()), Value);
}
