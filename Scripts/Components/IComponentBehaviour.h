#pragma once

#include <MxEngine.h>

namespace ComponentSystem
{
    class IComponentBehaviour
    {
        protected:
        MxEngine::MxObject::Handle gameObject;
        
        public:
        bool isEnabled;

        IComponentBehaviour(MxEngine::MxObject::Handle gameObject) : gameObject(gameObject) {}

        virtual void Start() = 0;

        virtual void Update() = 0;

        virtual void OnEnable() = 0;
    };  
}
