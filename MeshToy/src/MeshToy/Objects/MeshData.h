#pragma once

#include <vector>

#include <glm/glm.hpp>

struct Vertex
{
    glm::vec3 Position;
    glm::vec2 TexCoords;
};

class MeshData
{
public:
    MeshData();
    MeshData(std::vector<Vertex> InVertices, std::vector<unsigned int> InIndices);

    void Build();
    void Bind() const;
    void Draw() const;

private:
    std::vector<Vertex> Vertices;
    std::vector<unsigned int> Indices;
    
    unsigned int VBO = 0, VAO = 0, EBO = 0;
};
