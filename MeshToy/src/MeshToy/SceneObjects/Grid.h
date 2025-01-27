#pragma once

#include "SceneObject.h"

#include "MeshToy/Objects/Material.h"
#include "MeshToy/Objects/MeshData.h"

class Grid : public SceneObject
{
public:
    explicit Grid(const std::string& InName) : SceneObject(InName) {}
    
    void Start() override;
    void Render() override;

private:
    MeshData* Mesh = nullptr;
    Material* GridMaterial = nullptr;
};
