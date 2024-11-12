
#include "../Components/IComponentBehaviour.h"

using namespace MxEngine;

class Landscape : public ComponentSystem::IComponentBehaviour
{

    public:
    Landscape(MxObject::Handle& gameObject) : IComponentBehaviour(gameObject)
    {

    }

    virtual void Start() override
    {
        gameObject->Name = "Landscape";
        gameObject->AddComponent<MeshSource>(AssetManager::LoadMesh("Models/smallMounts.fbx"));
        auto renderer = gameObject->AddComponent<MeshRenderer>();          
        renderer->GetMaterial()->AlbedoMap = AssetManager::LoadTexture("Models/map_DefaultMaterial_BaseColor.png");
        gameObject->Transform.SetRotation({-90, 270, 0});
        gameObject->Transform.SetPosition({ 0.0f, 0.0f, 0.0f });
        auto collider = gameObject->AddComponent<BoxCollider>();
        auto rigidBody = gameObject->AddComponent<RigidBody>();
        rigidBody->SetMass(1.0f);
        rigidBody->SetLinearVelocity({0.0f, 0.0f, 0.0f});
        rigidBody->MakeKinematic();

        auto material = renderer->GetMaterial();
    }

    virtual void Update() override
    {
        return;
    }

    virtual void OnEnable() override
    {

    }
};