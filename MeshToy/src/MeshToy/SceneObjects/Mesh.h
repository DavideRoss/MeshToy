#pragma once

#include "SceneObject.h"
#include "MeshToy/Objects/Material.h"
#include "MeshToy/Objects/MeshData.h"

class Mesh : public SceneObject
{
public:
    explicit Mesh(const std::string& InName) : SceneObject(InName) {}
    Mesh(
        const std::string& InName,
        MeshData* InData,
        Material* InMaterial
    );

    void Start() override;
    void Update() override;
    void Render() override;

public:
    glm::vec3 GetPosition() const { return Position; }
    void SetPosition(const glm::vec3& InPosition) { Position = InPosition; bIsDirty = true; }

    glm::vec3 GetScale() const { return Scale; }
    void SetScale(const glm::vec3& InScale) { Scale = InScale; bIsDirty = true; }

    float GetRotation() const { return Rotation; }
    void SetRotation(const float InRotation) { Rotation = InRotation; bIsDirty = true; }

private:
    glm::vec3 Position = glm::vec3(0, 0, 0);
    glm::vec3 Scale = glm::vec3(1, 1, 1);
    float Rotation = 0.0f;

private:
    MeshData* Data = nullptr;
    Material* Material = nullptr;
    glm::mat4 Model = glm::mat4(1.0f);

    // TODO: set to false when there are the proper checks
    bool bIsDirty = true;
};
