#include "Material.h"

#include <format>
#include <iostream>
#include <glm/gtc/type_ptr.hpp>

#include "MeshToy/Utils/ShaderCompiler.h"

Material::Material(const std::string& InMaterialName)
    : MaterialName(InMaterialName)
{
    std::string VertexSource;
    if (!ShaderCompiler::OpenFile(std::format("shaders/{}.vert", InMaterialName), VertexSource))
    {
        // TODO: convert to use log macros
        std::cerr << std::format("Cannot open vertex shader for material {}!\n", InMaterialName);
        return;
    }

    std::string FragmentSource;
    if (!ShaderCompiler::OpenFile(std::format("shaders/{}.frag", InMaterialName), FragmentSource))
    {
        std::cerr << std::format("Cannot open fragment shader for material {}!\n", InMaterialName);
        return;
    }

    std::string CompileError;
    unsigned int VertexShaderPtr;
    if (!ShaderCompiler::CompileShader(GL_VERTEX_SHADER, VertexSource, VertexShaderPtr, CompileError))
    {
        std::cerr << "Cannot compile vertex shader:\n" << CompileError << '\n';
        return;
    }

    unsigned int FragmentShaderPtr;
    if (!ShaderCompiler::CompileShader(GL_FRAGMENT_SHADER, FragmentSource, FragmentShaderPtr, CompileError))
    {
        std::cerr << "Cannot compile fragment shader:\n" << CompileError << '\n';
        return;
    }

    ProgramPtr = glCreateProgram();
    glAttachShader(ProgramPtr, VertexShaderPtr);
    glAttachShader(ProgramPtr, FragmentShaderPtr);
    glLinkProgram(ProgramPtr);

    int Success;
    glGetProgramiv(ProgramPtr, GL_LINK_STATUS, &Success);
    if (!Success)
    {
        char Log[512];
        glGetProgramInfoLog(ProgramPtr, 512, nullptr, Log);
        std::cerr << "Cannot link material " << InMaterialName << ":\n" << Log << '\n';
        return;
    }

    glDeleteShader(VertexShaderPtr);
    glDeleteShader(FragmentShaderPtr);

    // TODO: use define to get the global data
    const unsigned int UniformBlockIndex = glGetUniformBlockIndex(ProgramPtr, "Matrices");
    if (UniformBlockIndex != GL_INVALID_INDEX)
    {
        glUniformBlockBinding(ProgramPtr, UniformBlockIndex, 0);
    }
}

void Material::Use() const
{
    glUseProgram(ProgramPtr);

    int Index = 0;
    for (const auto& [ParameterName, TexturePtr] : Textures)
    {
        SetInt(ParameterName, Index);
        glActiveTexture(GL_TEXTURE0 + Index);
        TexturePtr->Use();

        // TODO: there's the risk going OOB
        // TODO: check https://registry.khronos.org/OpenGL-Refpages/gl4/html/glActiveTexture.xhtml
        Index++;
    }
}

void Material::SetFloat(const std::string& ParameterName, float Value) const
{
    glUniform1f(glGetUniformLocation(ProgramPtr, ParameterName.c_str()), Value);
}

void Material::SetInt(const std::string& ParameterName, int Value) const
{
    glUniform1i(glGetUniformLocation(ProgramPtr, ParameterName.c_str()), Value);
}

void Material::SetVector4(const std::string& ParameterName, float X, float Y, float Z, float W) const
{
    glUniform4f(
        glGetUniformLocation(ProgramPtr, ParameterName.c_str()),
        X, Y, Z, W
    );
}

void Material::SetVector4(const std::string& ParameterName, glm::vec4 Value) const
{
    glUniform4f(
        glGetUniformLocation(ProgramPtr, ParameterName.c_str()),
        Value.x, Value.y, Value.z, Value.w
    );
}

void Material::SetMatrix4(const std::string& ParameterName, const glm::mat4& Value) const
{
    glUniformMatrix4fv(
        glGetUniformLocation(ProgramPtr, ParameterName.c_str()),
        1, GL_FALSE, glm::value_ptr(Value)
    );
}

void Material::SetTexture(const std::string& ParameterName, const Texture* InTexture)
{
    if (Textures.contains(ParameterName))
    {
        // TODO: add warning
        return;
    }

    Textures.insert({ ParameterName, InTexture });
}
