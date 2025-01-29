#pragma once

#include <map>
#include <string>

#include <glm/vec2.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>

#include "MeshToy/Objects/Material.h"

class Gizmos
{
public:
    static void DrawCircle(glm::vec2 Position, float Radius);
    
public:
    static glm::vec4 Color;

private:
    static Material* FindOrLoadMaterial(const std::string& MaterialName);

private:
    static std::map<std::string, Material*> Materials;
    
};
