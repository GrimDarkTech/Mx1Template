#include <iostream>
#include <string>
#include <thread>

#include <MxEngine.h>

#include "../Scripts/Components/ComponentManager.h"
#include "../Scripts/Drone/Drone.h"
#include "../Scripts/Drone/NavigationAgent.h"
#include "../Scripts/Landscape/Landscape.h"
#include "../Scripts/Light/Lights.h"
#include "../Scripts/Camera/CameraCreator.h"
#include "../Scripts/Camera/CameraMovement.h"
#include "../Scripts/Raycast/Raycaster.h"
#include "../Scripts/Entity/Marker.h"


namespace Drone
{
    using namespace MxEngine;

    class MxApplication : public Application
    {
		private:
		NavigationAgent _agent;
		CameraMovement _cameraMovement;
	
    	public:

		MxObject::Handle cameraObject;
		MxObject::Handle drone;
		MxObject::Handle terrain;



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
			}

		}


        virtual void OnCreate() override
        {
			this->cameraObject = MxObject::Create();
			CameraCreator cameraCreator(cameraObject, Vector3(0, 0, 0));
			ComponentSystem::ComponentManager::AddComponent(cameraCreator);
			
			this->terrain = MxObject::Create();
			Landscape landscape(terrain);
			ComponentSystem::ComponentManager::AddComponent(landscape);

			auto pointLight = MxObject::Create();
			Lights lights(pointLight, Vector3(0, 10, 0));
			ComponentSystem::ComponentManager::AddComponent(lights);

			this->drone = MxObject::Create();
			this->drone->Transform.SetPosition(Vector3(0, 0, 0));
			UAV uav(drone);;
			ComponentSystem::ComponentManager::AddComponent(uav);
			
			_agent.Start(drone);
			_agent.SetVelocity(2);
			_agent.moveMode = AgentMode::Teleport;

			_cameraMovement.Start(cameraObject);
			_cameraMovement.SetTarget(drone);
			_cameraMovement.offset = Vector3(0, 2, 0);
			_cameraMovement.mode = CameraMode::Free;
		}

        virtual void OnUpdate() override
        {
			try
			{
				_cameraMovement.Update();
				_agent.Update();
			}
			catch (const char* error_message)
			{
				Logger::Log(VerbosityType::ERROR, error_message);
			}

			if (Input::IsKeyPressed(KeyCode::I)) 
			{
				_cameraMovement.mode = static_cast<CameraMode>((static_cast<int>(_cameraMovement.mode) + 1) % 2);
			}

			if (Input::IsKeyPressed(KeyCode::ENTER)) 
			{
				if(!_agent.isMoving)
				{
					_agent.FollowRoute(true);
				}
				else
				{
					_agent.isMoving = false;
				}
			}

			if (Input::IsMousePressed(MouseButton::LEFT)) 
			{
				Vector3 position = cameraObject->Transform.GetPosition();
				Marker::CreateMarker(position, Vector3(0.05, 0.05, 0.05), Vector3(1, 0, 0));
				_agent.AddRoutePosition(position);
			}
			
			if (Input::IsKeyPressed(KeyCode::F)) {
				Scene::Save("scene.json");
				Logger::Log(VerbosityType::INFO, "scene save");
			}
        }

        virtual void OnDestroy() override
        {
        }
	};
}

int main()
{
    MxEngine::LaunchFromSourceDirectory();
    Drone::MxApplication app;
    app.Run();
    return 0;
}

