#include "Quad.h"

Quad::Quad()
{
    Vertices = {
        { { -1.0f,  1.0f, 0.0f }, { 0.0f, 1.0f } },
        { { -1.0f, -1.0f, 0.0f }, { 0.0f, 0.0f } },
        { { 1.0f,  1.0f, 0.0f }, { 1.0f, 1.0f } },
        { { 1.0f, -1.0f, 0.0f }, { 1.0f, 0.0f } },
    };
    
    Indices = {
        0, 1, 3,
        0, 2, 3
    };
}

MeshData* Quad::BuildStaticMesh() const
{
    return new MeshData(Vertices, Indices);
}
