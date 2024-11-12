
#include "../Components/IComponentBehaviour.h"

using namespace MxEngine;

class CameraCreator : public ComponentSystem::IComponentBehaviour
{
        private:
        Vector3 position;

        public:
        CameraCreator(MxObject::Handle gameObject, Vector3& position) : IComponentBehaviour(gameObject)
        {
            this->position = position;
        }

        virtual void Start() override
        {
			gameObject->Name = "Camera";
			gameObject->Transform.SetPosition(position);
		
			auto controller = gameObject->AddComponent<CameraController>();
			controller->ListenWindowResizeEvent();
            controller->SetCameraType(CameraType::PERSPECTIVE);
			Rendering::SetViewport(controller);

            auto input = gameObject->AddComponent<InputController>();
			input->BindMovement(KeyCode::W, KeyCode::A, KeyCode::S, KeyCode::D, KeyCode::SPACE, KeyCode::LEFT_SHIFT);
            input->BindRotation();

			Input::SetCursorMode(MxEngine::CursorMode::DISABLED);
        }

        virtual void Update() override
        {
            
        }

        virtual void OnEnable() override
        {

        }
};