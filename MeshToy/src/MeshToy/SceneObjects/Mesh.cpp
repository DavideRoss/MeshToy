#include "Mesh.h"

#include <glm/ext/matrix_transform.hpp>

#include "MeshToy/MeshToyApp.h"

Mesh::Mesh(const std::string& InName, MeshData* InData, ::Material* InMaterial)
    : SceneObject(InName), Data(InData), Material(InMaterial)
{
}

void Mesh::Start()
{
    Data->Build();
    Material->SetMatrix4("Model", glm::mat4(1.0f));
}

void Mesh::Update()
{
    if (bIsDirty)
    {
        // TODO: uncomment when controls are in place
        // bIsDirty = false;

        Model = glm::translate(glm::mat4(1.0f), Position);
        Model = glm::scale(Model, Scale);
        Model = glm::rotate(Model, glm::radians(Rotation), glm::vec3(0, 0, -1));

        Material->SetMatrix4("Model", Model);
    }
}

void Mesh::Render()
{
    Material->Use();
    Data->Draw();
}
