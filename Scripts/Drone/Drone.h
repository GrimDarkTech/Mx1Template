#include "../Components/IComponentBehaviour.h"

using namespace MxEngine;

class UAV : public ComponentSystem::IComponentBehaviour
{
        public:
        Vector3 position;

        UAV(MxObject::Handle& gameObject) : IComponentBehaviour(gameObject)
        {

        }

        virtual void Start() override
        {
            gameObject->Name = "Drone";

            gameObject->AddComponent<MeshSource>(AssetManager::LoadMesh("Models/Drone.fbx"));
			auto renderer = gameObject->AddComponent<MeshRenderer>(AssetManager::LoadMaterials("Models/Drone.fbx"));
			gameObject->Transform.SetRotation({ 270.0f, 0.0f, 0.0f });
			gameObject->Transform.SetScale({ 0.5f, 0.5f, 0.5f });
			gameObject->Transform.SetPosition(position);

			auto material = renderer->GetMaterial();
            material->BaseColor = Vector3(1, 0, 0);
        }

        virtual void Update() override
        {

        }

        virtual void OnEnable() override
        {

        }
};