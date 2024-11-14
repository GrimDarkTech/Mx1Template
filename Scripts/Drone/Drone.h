
#include "../Components/IComponentBehaviour.h"

using namespace MxEngine;

class UAV : public ComponentSystem::IComponentBehaviour
{
        public:

        UAV(MxObject::Handle gameObject) : IComponentBehaviour(gameObject)
        {
        }

        virtual void Start() override
        {
            gameObject->Name = "Drone";

            auto mesh = gameObject->AddComponent<MeshSource>(AssetManager::LoadMesh("Models/Drone_plane2.fbx"));
            TransformComponent meshTransform;
            meshTransform.SetRotation(Vector3(90, 0, -90));
            mesh->Mesh->GetSubMeshByIndex(0).SetTransform(meshTransform);
			auto renderer = gameObject->AddComponent<MeshRenderer>();

            renderer->GetMaterial()->AlbedoMap = AssetManager::LoadTexture("Models/Drone_DefaultMaterial_BaseColor.png");
			gameObject->Transform.SetRotation({ 0, 0.0f, 0.0f });
			gameObject->Transform.SetScale({ 0.5f, 0.5f, 0.5f });

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