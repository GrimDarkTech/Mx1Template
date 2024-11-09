
#include "../Components/IComponentBehaviour.h"

using namespace MxEngine;

class Lights : public ComponentSystem::IComponentBehaviour
{

    private:
    Vector3 positon;

    public:
    Lights(MxObject::Handle& gameObject, Vector3& position) : IComponentBehaviour(gameObject)
    {
        this->positon = position;
    }

    virtual void Start() override
    {   
        gameObject->Name = "Lights";
        gameObject->Transform.SetPosition(positon);

        auto lightSource = gameObject->AddComponent<PointLight>();
        lightSource->SetColor(Vector3(1.0f, 0.7f, 0.3f));
        lightSource->SetIntensity(1.0f);
        lightSource->SetRadius(100);
    }

    virtual void Update() override
    {
        
    }

    virtual void OnEnable() override
    {

    }
};