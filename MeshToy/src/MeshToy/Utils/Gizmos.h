#pragma once

#include <map>
#include <string>

#include <glm/vec2.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>

#include "MeshToy/Objects/Material.h"

struct CubicBezier
{
   glm::vec2 P0;
   glm::vec2 P1;
   glm::vec2 P2;
   glm::vec2 P3;
};

class Gizmos
{
public:
    static void DrawCircle(glm::vec2 Position, float Radius);
    static void DrawLine(glm::vec2 Start, glm::vec2 End, float Thickness);
    static void DrawBezier(glm::vec2 P0, glm::vec2 P1, glm::vec2 P2, glm::vec2 P3, float Thickness);
    
public:
    static glm::vec4 Color;

private:
    static Material* FindOrLoadMaterial(const std::string& MaterialName);

    // Bezier
    static glm::vec2 EvaluateCubic(float T, const CubicBezier& Curve);
    static void SolveQuadratic(float A, float B, float C, const CubicBezier& Curve, std::vector<glm::vec2>& Candidates);

    static void GenerateQuad(glm::vec2 TopLeft, glm::vec2 BottomRight);
    static void Draw();

private:
    static std::map<std::string, Material*> Materials;
    
};
