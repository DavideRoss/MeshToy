#pragma once

#include <string>
#include <vector>

#include <glad/glad.h>

class ShaderCompiler
{
public:
    static bool OpenFile(const std::string& Path, std::string& OutData, bool bSkipExtensions = false);
    static bool CompileShader(const GLenum Type, const std::string& Source, unsigned int& OutShaderPtr, std::string& OutError);

private:
    static void CheckForIncludes(const std::string& Source, std::vector<std::string>& OutIncludes);
    static void AddIncludeShader(const std::string& Path, std::vector<std::string>& OutIncludes);

    
private:
    static std::vector<std::string> Includes;

    static std::vector<std::string> Extensions;
};
