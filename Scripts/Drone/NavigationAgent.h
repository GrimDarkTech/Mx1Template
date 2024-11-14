#include <iostream>

using namespace MxEngine;

enum class AgentMode
{
    Teleport,
    TeleportAndRotate
};

class NavigationAgent
{
    private:
    std::vector<MxEngine::Vector3> _routePositions;
    float _velocity;
    int _currentPoint;
    MxEngine::MxObject::Handle gameObject;
    Vector3 _velocityVector = Vector3(0, 0, 0);
    bool isStarted = false;
    
    public:
    bool isMoving;
    Vector3 rotation;
    AgentMode moveMode;

    NavigationAgent()
    {
    }

    void Start(MxEngine::MxObject::Handle gameObject)
    {
        this->gameObject = gameObject;
        _routePositions = {};
        isMoving = false;
        _velocity = 0;
        _currentPoint = 0;
        this->_velocity = 0;
        isStarted = true;
    }

    void Update()
    {
        if(isStarted && isMoving && _routePositions.size() > _currentPoint)
        {
            Vector3 targetPositon = _routePositions[_currentPoint];
            Vector3 delta = targetPositon - gameObject->Transform.GetPosition();
            Vector3 direction;

            if(Length2(delta) > 0.01)
            {
                direction = Normalize(delta);
            }
            else 
            {
                direction = Vector3(0, 0, 0);
                _currentPoint ++;
            }

            if(moveMode == AgentMode::TeleportAndRotate)
            {
                float xAngle = atan2(direction.y, direction.z);
                float yAngle = atan2(direction.x, direction.z);
                float zAngle = atan2(direction.y, direction.x);

                if((yAngle < -0.01 || yAngle > 0.01) && (xAngle < -0.01 || xAngle > 0.01))
                {
                    Vector3 rot = Vector3(0, yAngle, zAngle) * 57.29577f + rotation;
                    gameObject->Transform.SetRotation(rot);
                }
            }

            _velocityVector = direction *_velocity;
            gameObject->Transform.SetPosition(gameObject->Transform.GetPosition() + direction *_velocity * Time::Delta());
        }
    }

    void AddRoutePosition(MxEngine::Vector3 position)
    {
        _routePositions.push_back(position);
    }

    void SetVelocity(float velocity)
    {
        velocity = abs(velocity);
        _velocity = velocity;
    }

    Vector3 GetVelocityVector()
    {
        return _velocityVector;
    }

    void PrintRoute()
    {
        for (int i = 0; i < _routePositions.size(); i++)
        {
            Logger::Log(VerbosityType::INFO, ("Position " + std::to_string(i) + " : (" + std::to_string(_routePositions[i].x) + " ; " + std::to_string(_routePositions[i].y) + " ; " + std::to_string(_routePositions[i].z) + ")").c_str());
        }
    }

    void FollowRoute(bool isResetCurrentPoint)
    {
        isMoving = true;
        if(isResetCurrentPoint)
        {
            _currentPoint = 0;
        }
    }
};