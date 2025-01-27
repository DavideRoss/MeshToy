#pragma once

#include "MeshToy/Objects/MeshData.h"

// TODO: derive a class, maybe static mesh?
class Quad
{
public:
    Quad();

    // TODO: return a pointer instead?
    MeshData* BuildStaticMesh() const;

private:
    std::vector<Vertex> Vertices;
    std::vector<unsigned int> Indices;
};
