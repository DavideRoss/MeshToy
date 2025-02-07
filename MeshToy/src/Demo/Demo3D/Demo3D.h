#pragma once

#include "MeshToy/MeshToyApp.h"
#include "MeshToy/Objects/MeshData.h"

class Demo3D : public MeshToyApp
{
public:
    Demo3D();

    void Start() override;

private:
    MeshData Cube;
};
