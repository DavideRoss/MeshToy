#include "Grid.h"

void Grid::Start()
{
    std::vector<Vertex> Vertices = {
        { { -1.0f,  1.0f, 0.0f }, { 0.0f, 1.0f } },
        { { -1.0f, -1.0f, 0.0f }, { 0.0f, 0.0f } },
        { { 1.0f,  1.0f, 0.0f }, { 1.0f, 1.0f } },
        { { 1.0f, -1.0f, 0.0f }, { 1.0f, 0.0f } },
    };
    
    std::vector<unsigned int> Indices = {
        0, 1, 3,
        0, 2, 3
    };

    Mesh = new MeshData(Vertices, Indices);

    GridMaterial = new Material("Grid");
}

void Grid::Render()
{
    GridMaterial->Use();
    Mesh->Draw();
}
