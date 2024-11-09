#include <iostream>
#include <MxEngine.h>

using namespace MxEngine;

enum class CameraMode {Free, Follow};

class CameraMovement
{
    private:
    MxEngine::MxObject::Handle gameObject;
    MxEngine::MxObject::Handle target;
    
    public:
    CameraMode mode;
    Vector3 offset;

    CameraMovement()
    {
    }

    void Start(MxEngine::MxObject::Handle gameObject)
    {
        this->gameObject = gameObject;
    }

    void SetTarget(MxEngine::MxObject::Handle target)
    {
        this->target = target;
    }

    void Update()
    {
        if(mode == CameraMode::Follow)
        {
            if(target.IsValid())
            {
                gameObject->Transform.SetPosition(target->Transform.GetPosition() + offset);
            }
        }

    }
};