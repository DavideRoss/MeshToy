#include "Gizmos.h"

#include <vector>

#include <glad/glad.h>
#include <glm/vec3.hpp>

glm::vec4 Gizmos::Color = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
std::map<std::string, Material*> Gizmos::Materials;

void Gizmos::DrawCircle(glm::vec2 Position, float Radius)
{
    const glm::vec3 Position3D = glm::vec3(Position.x, Position.y, 0.0f);
    const std::vector<glm::vec3> Vertices = {
        glm::vec3(-Radius,  Radius, 0.0f) + Position3D,
        glm::vec3(-Radius, -Radius, 0.0f) + Position3D,
        glm::vec3(Radius,  Radius, 0.0f) + Position3D,
        glm::vec3(Radius, -Radius, 0.0f) + Position3D
    };
    
    // TODO: I don't really need indices maybe, triangle strip should be enough
    const std::vector<unsigned int> Indices = {
        0, 1, 3,
        0, 2, 3
    };
    
    unsigned int VAO, VBO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, 4 * sizeof(glm::vec3), Vertices.data(), GL_STATIC_DRAW);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), Indices.data(), GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), nullptr);
    glEnableVertexAttribArray(0);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    
    const Material* CircleMaterial = FindOrLoadMaterial("SDF_Circle");
    CircleMaterial->Use();
    CircleMaterial->SetVector4("Color", Gizmos::Color);
    CircleMaterial->SetVector2("Position", Position);
    CircleMaterial->SetFloat("Radius", Radius);

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
    glBindVertexArray(0);
}

Material* Gizmos::FindOrLoadMaterial(const std::string& MaterialName)
{
    if (Materials.contains(MaterialName)) return Materials[MaterialName];

    Material* NewMaterial = new Material(MaterialName);
    NewMaterial->Use();
    NewMaterial->SetMatrix4("Model", glm::mat4(1.0f));
    
    Materials[MaterialName] = NewMaterial;
    return NewMaterial;
}
