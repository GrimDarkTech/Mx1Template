#include <iostream>
#include <string>
#include <thread>

#include <MxEngine.h>

#include "../Scripts/Drone/Drone.h"
#include "../Scripts/Landscape/Landscape.h"


namespace Drone
{
    using namespace MxEngine;

    class MxApplication : public Application
    {
    public:
		
		bool edit_mode = false;
		float up_scale = 0.5f;

		MxObject::Handle cameraObject;
		MxObject::Handle drone;

		void CreateMarker(Vector3 position)
		{
			auto sphere = MxObject::Create();
			sphere->AddComponent<MeshSource>(Primitives::CreateSphere());
			sphere->AddComponent<MeshRenderer>();
			sphere->AddComponent<SphereCollider>();
			sphere->Transform.SetPosition(position);
			sphere->Transform.SetScale({ 0.05f, 0.05f, 0.05f });
		}

		
		void EditCamMode() 
		{
			cameraObject->Transform.SetPosition({ 0.0f, 0.5f, 0.0f });

			auto controller = cameraObject->AddComponent<CameraController>();
			controller->ListenWindowResizeEvent();

			controller->SetRotation({ 0.0f, -90.0f});
			controller->SetCameraType(MxEngine::CameraType::ORTHOGRAPHIC);
			Rendering::SetViewport(controller);

			auto input = cameraObject->AddComponent<InputController>();
			input->BindMovement(KeyCode::W, KeyCode::A, KeyCode::S, KeyCode::D, KeyCode::SPACE, KeyCode::LEFT_SHIFT);
         
			Input::SetCursorMode(MxEngine::CursorMode::NORMAL);
			auto cursorPosition = Input::GetCursorPosition();
			//Logger::Log(VerbosityType::INFO, cursorPosition);
			
		}

		void DemoCamMode() 
		{
			auto controller = cameraObject->AddComponent<CameraController>();
			controller->ListenWindowResizeEvent();
			Rendering::SetViewport(controller);

			Input::SetCursorMode(MxEngine::CursorMode::DISABLED);

			auto input = cameraObject->AddComponent<InputController>();
			input->BindMovement(KeyCode::W, KeyCode::A, KeyCode::S, KeyCode::D, KeyCode::SPACE, KeyCode::LEFT_SHIFT);
			input->BindRotation();
		}

		void CreateCamera()
		{
			cameraObject = MxObject::Create();
			cameraObject->Name = "Camera Object";
			cameraObject->Transform.SetPosition({ 0.0f, 0.5f, 0.0f });
		
			auto controller = cameraObject->AddComponent<CameraController>();
			controller->ListenWindowResizeEvent();
			Rendering::SetViewport(controller);
			
			EditCamMode();
		}

		void LightInit()
		{
			auto pointLight = MxObject::Create();
            auto lightSource = pointLight->AddComponent<SpotLight>();
            
            lightSource->SetColor(Vector3(1.0f, 0.7f, 0.0f));
			lightSource->SetIntensity(100.0f);
            pointLight->Transform.SetPosition({ 0.0f, 20.0f, 0.0f });
		}

		void OnMouseClick()
		{
			Vector2 mousePosition = Input::GetCursorPosition();
			Vector2 windowSize = GlobalConfig::GetWindowSize();

			std::cout << "Mouse: (" <<  (mousePosition.x / windowSize.x) * 2 - 1.0f << ", " << (mousePosition.y / windowSize.y) * 2 - 1.0f<< ")" << std::endl;

			auto controller = cameraObject->GetComponent<CameraController>();

			Vector3 cameraPosition = cameraObject->Transform.GetPosition(); // Позиция камеры 

			Vector3 rayDirection = controller->GetDirection(); 

			float ratio = controller->Camera.GetAspectRatio();
			float scaleFactor = -10.0f;
			Vector3 offset = Vector3(((mousePosition.x / windowSize.x) * 2 - 1.0f) * scaleFactor * ratio, 0, ((mousePosition.y / windowSize.y) * 2 - 1.0f) * scaleFactor);

			float castDistance = 10;
			
			Vector3 targetPosition = cameraPosition + offset + rayDirection * castDistance;

			// Выполняем raycast
			float fraction = 0;
    
			auto hitResult = Physics::RayCast(cameraPosition, targetPosition, fraction);
			if(hitResult.IsValid())
			{
				MXLOG_INFO("raycast", "found object: " + hitResult->Name);
			}

			std::cout << "Fraction: " << fraction << std::endl;;

			if (fraction < 1)
			{	
				Logger::Log(VerbosityType::INFO, "Raycast done!");
				Vector3 hitPoint = cameraPosition + (targetPosition - cameraPosition) * fraction;
				//hitPoint.y += up_scale;
				std::cout << "HitPoint: (" << hitPoint.x << ", " << hitPoint.y << ", " << hitPoint.z << ")" << std::endl;
				std::cout << "CameraCenter: (" << cameraPosition.x << ", " << cameraPosition.y << ", " << cameraPosition.z << ")" << std::endl;
				CreateMarker(hitPoint);
			}

		}

		void MoveObjectToPosition(MxObject::Handle& object, const Vector3& targetPosition, float deltaTime) 
		{
			Vector3 currentPosition = object->Transform.GetPosition();
			// Задаем скорость перемещения
			float speed = 5.0f; // скорость в единицах в секунду

			// Линейная интерполяция 
			Vector3 newPosition = glm::mix(currentPosition, targetPosition, speed * deltaTime);
    
			// Устанавливаем новую позицию 
			object->Transform.SetPosition(newPosition);
		}
		



		////////////////////Основные функции////////////////////
        virtual void OnCreate() override
        {
			CreateCamera();
			
			MxObject::Handle terrain = MxObject::Create();
			Landscape landscape(terrain);
			landscape.Start();

			LightInit();

			this->drone = MxObject::Create();
			UAV uav(drone);
			uav.Start();
        }

        virtual void OnUpdate() override
        {

			Vector3 targetPosition = Vector3(0.5, 1.5, -1);
			float velocity = 2.0f;

			Vector3 delta = targetPosition - drone->Transform.GetPosition();
			Vector3 direction;
			if(Length(delta) > 0.001f)
			{
				direction = Normalize(delta);
			}
			else
			{
				direction = Vector3(0, 0, 0);
			}

			drone->Transform.SetPosition(drone->Transform.GetPosition() + direction * velocity * Time::Delta());


			if (Input::IsKeyPressed(KeyCode::I)) {
				if (!edit_mode) {	
					edit_mode = true;
					Logger::Log(VerbosityType::INFO, "Change to Edit mode");
					DemoCamMode();
				} else if (edit_mode) {
					edit_mode = false;
					Logger::Log(VerbosityType::INFO, "Change to Demo mode");
					EditCamMode();	
				}
			}

			if (Input::IsMousePressed(MouseButton::LEFT)) {
				OnMouseClick();
			}
			
			if (Input::IsKeyPressed(KeyCode::F)) {
				Scene::Save("scene.json");
				Logger::Log(VerbosityType::INFO, "scene save");
			}
        }

        virtual void OnDestroy() override
        {
        }
		////////////////////////////////////////////////////////
	};
}

int main()
{
    MxEngine::LaunchFromSourceDirectory();
    Drone::MxApplication app;
    app.Run();
    return 0;
}

