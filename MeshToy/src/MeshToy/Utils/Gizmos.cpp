#include "Gizmos.h"

#include <vector>

#include <glad/glad.h>
#include <glm/vec3.hpp>

glm::vec4 Gizmos::Color = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
std::map<std::string, Material*> Gizmos::Materials;

// TODO: do not regenerate the vertices everytime
//       instead, create a unit quad and move it around with
//       the model matrix

void Gizmos::DrawCircle(const glm::vec2 Position, const float Radius)
{
    GenerateQuad(
        glm::vec2(-Radius, Radius) + Position,
        glm::vec2(Radius, -Radius) + Position
    );

    const Material* CircleMaterial = FindOrLoadMaterial("SDF_Circle");
    CircleMaterial->Use();
    CircleMaterial->SetVector4("Color", Gizmos::Color);
    CircleMaterial->SetVector2("Position", Position);
    CircleMaterial->SetFloat("Radius", Radius);

    Draw();
}

void Gizmos::DrawLine(const glm::vec2 Start, const glm::vec2 End, const float Thickness)
{
    glm::vec2 TopLeft(std::min(Start.x, End.x), std::max(Start.y, End.y));
    glm::vec2 BottomRight(std::max(Start.x, End.x), std::min(Start.y, End.y));

    TopLeft += glm::vec2(-Thickness, Thickness);
    BottomRight += glm::vec2(Thickness, -Thickness);

    GenerateQuad(TopLeft, BottomRight);

    const Material* LineMaterial = FindOrLoadMaterial("SDF_Line");
    LineMaterial->Use();
    LineMaterial->SetVector4("Color", Gizmos::Color);
    LineMaterial->SetVector2("Start", Start);
    LineMaterial->SetVector2("End", End);
    LineMaterial->SetFloat("Thickness", Thickness);

    Draw();
}

void Gizmos::DrawBezier(glm::vec2 P0, glm::vec2 P1, glm::vec2 P2, glm::vec2 P3, float Thickness)
{
    const glm::vec2 A = 3.0f * P3 - 9.0f * P2 + 9.0f * P1 - 3.0f * P0;
    const glm::vec2 B = 6.0f * P0 - 12.0f * P1 + 6.0f * P2;
    const glm::vec2 C = 3.0f * P1 - 3.0f * P0;

    CubicBezier Curve(P0, P1, P2, P3);
    std::vector<glm::vec2> Candidates = { P0, P3 };

    SolveQuadratic(A.x, B.x, C.x, Curve, Candidates);
    SolveQuadratic(A.y, B.y, C.y, Curve, Candidates);

    glm::vec2 MinPoint = Candidates[0];
    glm::vec2 MaxPoint = Candidates[0];
    for (const glm::vec2& P : Candidates)
    {
        MinPoint = glm::min(MinPoint, P);
        MaxPoint = glm::max(MaxPoint, P);
    }

    glm::vec2 ThicknessVector(Thickness, Thickness);
    MinPoint -= ThicknessVector;
    MaxPoint += ThicknessVector;
    
    
    GenerateQuad(MinPoint, MaxPoint);

    const Material* CurveMaterial = FindOrLoadMaterial("SDF_CubicBezier");
    CurveMaterial->Use();
    CurveMaterial->SetVector4("Color", Gizmos::Color);
    CurveMaterial->SetVector2("P0", P0);
    CurveMaterial->SetVector2("P1", P1);
    CurveMaterial->SetVector2("P2", P2);
    CurveMaterial->SetVector2("P3", P3);
    CurveMaterial->SetFloat("Thickness", Thickness);

    Draw();
}

// ================================================================================================
// PRIVATE FUNCTIONS
// ================================================================================================

Material* Gizmos::FindOrLoadMaterial(const std::string& MaterialName)
{
    if (Materials.contains(MaterialName)) return Materials[MaterialName];

    Material* NewMaterial = new Material(MaterialName);
    Materials[MaterialName] = NewMaterial;
    return NewMaterial;
}

glm::vec2 Gizmos::EvaluateCubic(const float T, const CubicBezier& Curve)
{
    const float F = 1.0f - T;
    return
        Curve.P0 * F * F * F +
        3.0f * Curve.P1 * T * F * F +
        3.0f * Curve.P2 * T * T * F +
        Curve.P3 * T * T * T;
}

void Gizmos::SolveQuadratic(const float A, const float B, const float C, const CubicBezier& Curve, std::vector<glm::vec2>& Candidates)
{
    if (glm::abs(A) > 0.0f)
    {
        const float Disc = B * B - 4 * A * C;
        if (Disc > 0.0f)
        {
            const float SqrtDisc = sqrtf(Disc);
            const float T1 = (-B + SqrtDisc) / (2.0f * A);
            const float T2 = (-B - SqrtDisc) / (2.0f * A);

            if (T1 >= 0.0f && T1 <= 1.0f) Candidates.push_back(EvaluateCubic(T1, Curve));
            if (T2 >= 0.0f && T2 <= 1.0f) Candidates.push_back(EvaluateCubic(T2, Curve));
        }
    }
    else if (glm::abs(B) > 0.0f)
    {
        const float T = -C / B;
        if (T > 0.0f && T <= 1.0f) Candidates.push_back(EvaluateCubic(T, Curve));
    }
}

void Gizmos::GenerateQuad(glm::vec2 TopLeft, glm::vec2 BottomRight)
{
    const std::vector<glm::vec3> Vertices = {
        glm::vec3(TopLeft.x, TopLeft.y, 0.0f),
        glm::vec3(TopLeft.x, BottomRight.y, 0.0f),
        glm::vec3(BottomRight.x, TopLeft.y, 0.0f),
        glm::vec3(BottomRight.x, BottomRight.y, 0.0f),
    };

    unsigned int VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, 4 * sizeof(glm::vec3), Vertices.data(), GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), nullptr);
    glEnableVertexAttribArray(0);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Gizmos::Draw()
{
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glBindVertexArray(0);
}
