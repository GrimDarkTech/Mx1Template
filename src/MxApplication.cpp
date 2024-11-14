#include <iostream>
#include <string>
#include <thread>

#include <MxEngine.h>

#include "../Scripts/Components/ComponentManager.h"
#include "../Scripts/Drone/Drone.h"
#include "../Scripts/Drone/NavigationAgent.h"
#include "../Scripts/Landscape/Landscape.h"
#include "../Scripts/Landscape/HeigthmapImporter.h"
#include "../Scripts/Light/Lights.h"
#include "../Scripts/Camera/CameraCreator.h"
#include "../Scripts/Camera/CameraMovement.h"
#include "../Scripts/Camera/CameraRotation.h"
#include "../Scripts/Raycast/Raycaster.h"
#include "../Scripts/Entity/Marker.h"
#include "../Scripts/GUI/Vector3GUI.h"


namespace Drone
{
    using namespace MxEngine;

    class MxApplication : public Application
    {
		private:
		NavigationAgent _agent;
		CameraMovement _cameraMovement;
		CameraRotation _cameraRotation;
		HeigthmapImporter _heigthmapImporter;

		float _velocity = 0;
		Vector3 _startPosition = Vector3(0, 0, 0);
	
    	public:
		MxObject::Handle cameraObject;
		MxObject::Handle drone;
		MxObject::Handle terrain;
		Vector3 targetPointOffset = Vector3(0, 0.05 ,0);
		Vector3 droneVelocity;


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
			this->drone->Transform.SetPosition(_startPosition);
			UAV uav(drone);;
			ComponentSystem::ComponentManager::AddComponent(uav);
			
			_agent.Start(drone);
			_agent.SetVelocity(_velocity);
			_agent.rotation = Vector3(0, 0, 180);
			_agent.moveMode = AgentMode::TeleportAndRotate;

			_cameraMovement.SetCamera(cameraObject);
			_cameraMovement.SetTarget(drone);
			_cameraMovement.offset = Vector3(0, 2, 0);
			_cameraMovement.mode = CameraMode::Free;

			_cameraRotation.SetInputController(cameraObject->GetComponent<InputController>());

			_heigthmapImporter.Import(Vector3(0, 0, 0), "Textures/Heightmap.png", 0.05, 15);
		}

        virtual void OnUpdate() override
        {
			try
			{
				_cameraMovement.Update();
				_agent.Update();
				Vector3GUI::DrawGUI(_agent.GetVelocityVector(), "Velocity m/s");
				Vector3GUI::DrawGUILabels(drone->Transform.GetPosition(), "Position GPS", "' Longitude", "' Altitude", "' Latitude");
				Vector3GUI::DrawGUILabels(drone->Transform.GetRotation(), "Rotation Gyro", "Pitch", "Yaw", "Roll");

				ImGui::Begin("Drone velocity m/s");
        		ImGui::InputFloat("Velocity", &_velocity);
 				ImGui::End();

				Vector3GUI::DrawGUIReference(_startPosition, "Press R to create new drone");
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

				auto camera = cameraObject->GetComponent<CameraController>();
				auto perspectiveCamera = camera->GetCamera<PerspectiveCamera>();

				float nearClip = perspectiveCamera.GetZNear();
				float fieldOfView = Radians(perspectiveCamera.GetFOV());
        		float aspectRatio = perspectiveCamera.GetAspectRatio();

        		float halfWidth = tan(fieldOfView * 0.5) * nearClip;
        		float halfHeight = halfWidth / aspectRatio;

				Vector2 mousePosition = Input::GetCursorPosition();
				Vector2 windowSize = GlobalConfig::GetWindowSize();

				float normalizedX = (mousePosition.x / windowSize.x) * 2 - 1;
				float normalizedY = (mousePosition.y / windowSize.y) * 2 - 1;

        		Vector3 direction = camera->GetDirection() * nearClip - Vector3(normalizedX * halfWidth * 2, normalizedY * halfHeight * 2, 0);
				direction = Normalize(direction);

				auto hit = Raycaster::Raycast(position, direction, 20);

				auto hitObject = std::get<0>(hit);
				auto hitPoint = std::get<1>(hit);
				auto hitDistance = std::get<2>(hit);

				if(hitObject.IsValid())
				{	
					std::srand(time(0));
					hitPoint += float(std::rand()%10) * targetPointOffset;
					Marker::CreateMarker(hitPoint, Vector3(0.05, 0.05, 0.05), Vector3(1, 0, 0));
					_agent.AddRoutePosition(hitPoint);
				}
			}

			if (Input::IsMousePressed(MouseButton::RIGHT))
			{
				_cameraRotation.SwitchRotationMode();			
			}

			if (Input::IsKeyPressed(KeyCode::R))
			{
				_agent.SetVelocity(_velocity);
				drone->Transform.SetPosition(_startPosition);
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

