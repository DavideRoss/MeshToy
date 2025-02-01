#include "Gizmos.h"

#include <vector>

#include <glad/glad.h>
#include <glm/vec3.hpp>

glm::vec4 Gizmos::Color = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
std::map<std::string, Material*> Gizmos::Materials;

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

    const Material* CircleMaterial = FindOrLoadMaterial("SDF_Line");
    CircleMaterial->Use();
    CircleMaterial->SetVector4("Color", Gizmos::Color);
    CircleMaterial->SetVector2("Start", Start);
    CircleMaterial->SetVector2("End", End);
    CircleMaterial->SetFloat("Thickness", Thickness);

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
