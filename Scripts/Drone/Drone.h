
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

            gameObject->AddComponent<MeshSource>(AssetManager::LoadMesh("Models/Drone.fbx"));
			auto renderer = gameObject->AddComponent<MeshRenderer>(AssetManager::LoadMaterials("Models/Drone.fbx"));
			gameObject->Transform.SetRotation({ 270.0f, 0.0f, 0.0f });
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