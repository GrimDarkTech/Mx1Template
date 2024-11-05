#include <MxEngine.h>
#include <iostream>

using namespace MxEngine;

class NavigationAgent : public Scriptable
{
    private:
    static std::vector<MxEngine::Vector3> _routePositions;
    static float _velocity;
    static int _currentPoint;
    
    public:
    static bool isMoving;

    virtual void OnCreate(MxObject& self) override 
    { 
        // _routePositions = {};
        // isMoving = false;
        // _velocity = 0;
        // _currentPoint = 0;
        this->_velocity = 0;
    }

    virtual void OnReload(MxObject& self) override 
    {
    }

    virtual void OnUpdate(MxObject& self) override 
    {
        // if(isMoving && _routePositions.size() > _currentPoint)
        // {
        //     Vector3 targetPositon = _routePositions[_currentPoint];
        //     Vector3 delta = targetPositon - self.Transform.GetPosition();
        //     Vector3 direction;

        //     if(Length2(delta) > 0.00001)
        //     {
        //         direction = Normalize(delta);
        //     }
        //     else 
        //     {
        //         direction = Vector3(0, 0, 0);
        //         _currentPoint ++;
        //     }

        //     self.Transform.SetPosition(self.Transform.GetPosition() + direction *_velocity * Time::Delta());
        // }
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
};

MXENGINE_RUNTIME_EDITOR(NavigationAgent);