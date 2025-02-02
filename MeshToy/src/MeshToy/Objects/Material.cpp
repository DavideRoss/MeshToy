#include "Material.h"

#include <filesystem>
#include <format>
#include <iostream>
#include <glm/gtc/type_ptr.hpp>
#include "yaml-cpp/yaml.h"

#include "MeshToy/Utils/Log.h"

#include "MeshToy/Utils/ShaderCompiler.h"

Material::Material(const std::string& InMaterialName)
    : MaterialName(InMaterialName)
{
    const std::string MaterialPath = std::format("materials/{}.yml", InMaterialName);

    if (!std::filesystem::exists(MaterialPath))
    {
        MESHTOY_EXCEPTION(std::format("Material definition for \"{}\" not found", InMaterialName));
    }
    
    YAML::Node MaterialDef = YAML::LoadFile(MaterialPath);
    YAML::Node ShadersDef = MaterialDef["shaders"];

    ProgramPtr = glCreateProgram();

    for (YAML::const_iterator It = ShadersDef.begin(); It != ShadersDef.end(); ++It)
    {
        std::string ShaderType = It->first.as<std::string>();
        std::string ShaderPath = It->second.as<std::string>();

        int ShaderEnum;
        if (ShaderType == "vertex") ShaderEnum = GL_VERTEX_SHADER;
        else if (ShaderType == "fragment") ShaderEnum = GL_FRAGMENT_SHADER;
        else MESHTOY_EXCEPTION("Shader type not recognized");

        std::string Source;
        if (!ShaderCompiler::OpenFile(std::format("shaders/{}", ShaderPath), Source))
        {
            // TODO: convert to use log macros
            std::cerr << std::format("Cannot open {} shader for material \"{}\"!\n", ShaderType, InMaterialName);
            return;
        }

        std::string CompileError;
        unsigned int ShaderPtr;
        if (!ShaderCompiler::CompileShader(ShaderEnum, Source, ShaderPtr, CompileError))
        {
            std::cerr << "Cannot compile vertex shader:\n" << CompileError << '\n';
            return;
        }

        glAttachShader(ProgramPtr, ShaderPtr);
        glDeleteShader(ShaderPtr);
    }

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

    // TODO: use define to get the global data
    // TODO: move it to material definition?
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

void Material::SetVector2(const std::string& ParameterName, float X, float Y) const
{
    glUniform2f(
        glGetUniformLocation(ProgramPtr, ParameterName.c_str()),
        X, Y
    );
}

void Material::SetVector2(const std::string& ParameterName, glm::vec2 Value) const
{
    glUniform2f(
        glGetUniformLocation(ProgramPtr, ParameterName.c_str()),
        Value.x, Value.y
    );
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
