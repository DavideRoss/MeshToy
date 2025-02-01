#include "ShaderCompiler.h"

#include <format>
#include <fstream>
#include <iostream>
#include <regex>
#include <sstream>

std::vector<std::string> ShaderCompiler::Includes;

std::vector<std::string> ShaderCompiler::Extensions = {
    "GL_ARB_shading_language_include"
};

bool ShaderCompiler::CompileShader(const GLenum Type, const std::string& Source, unsigned int& OutShaderPtr, std::string& OutError)
{
    std::vector<std::string> ShaderIncludes;
    CheckForIncludes(Source, ShaderIncludes);

    std::vector<const char*> CShaderIncludes;
    CShaderIncludes.reserve(ShaderIncludes.size());
    
    for (const std::string& Include : ShaderIncludes) CShaderIncludes.push_back(Include.c_str());

    OutShaderPtr = glCreateShader(Type);
    const char* CSource = Source.c_str();
    glShaderSource(OutShaderPtr, 1, &CSource, nullptr);
    glCompileShaderIncludeARB(
        OutShaderPtr,
        static_cast<GLsizei>(CShaderIncludes.size()),
        CShaderIncludes.data(),
        nullptr
    );

    int Success;
    glGetShaderiv(OutShaderPtr, GL_COMPILE_STATUS, &Success);
    if (!Success)
    {
        char Log[512];
        glGetShaderInfoLog(OutShaderPtr, 512, nullptr, Log);
        OutError = Log;
        return false;
    }

    return true;
}

void ShaderCompiler::CheckForIncludes(const std::string& Source, std::vector<std::string>& OutIncludes)
{
    std::regex const IncludeRegex("^#include \"(.+)\"");

    for (
        std::sregex_iterator Iter = std::sregex_iterator(Source.begin(), Source.end(), IncludeRegex);
        Iter != std::sregex_iterator();
        ++Iter
    )
    {
        const std::smatch& Match = *Iter;
        const std::string IncludePath = Match.str(1);

        if (std::ranges::find(Includes, IncludePath) == Includes.end())
        {
            AddIncludeShader(IncludePath, OutIncludes);
        }

        OutIncludes.emplace_back(IncludePath);
    }
}

void ShaderCompiler::AddIncludeShader(const std::string& Path, std::vector<std::string>& OutIncludes)
{
    std::string IncludeSource;
    if (!OpenFile("shaders" + Path, IncludeSource, true))
    {
        std::cerr << "[ShaderCompiler]: Failed to open include file: " << Path << '\n';
        return;
    }

    glNamedStringARB(GL_SHADER_INCLUDE_ARB, -1, Path.c_str(), -1, IncludeSource.c_str());
    Includes.push_back(Path);
    
    CheckForIncludes(IncludeSource, OutIncludes);
}

bool ShaderCompiler::OpenFile(const std::string& Path, std::string& OutData, bool bSkipExtensions)
{
    const std::ifstream Stream(Path);
    if (!Stream.is_open()) return false;

    std::stringstream FileBuffer;
    FileBuffer << Stream.rdbuf();
    OutData = FileBuffer.str();

    if (!bSkipExtensions)
    {
        std::string ExtensionsCode;
        for (const std::string& Extension : Extensions)
        {
            ExtensionsCode += std::format("#extension {} : require\n", Extension);
        }
        
        std::regex ExtensionRegex("#version (.*)\n$");
        OutData = std::regex_replace(OutData, ExtensionRegex, "#version $1\n" + ExtensionsCode);
    }
    
    return true;
}
