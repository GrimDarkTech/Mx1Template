#include <MxEngine.h>
#include <functional>
#include "IComponentBehaviour.h"

namespace ComponentSystem
{
    class ComponentManager
    {
        public:
        static std::vector<std::reference_wrapper<IComponentBehaviour>> components;

        static void CallUpdate()
        {
            for (auto component : components)
            {
                if(component.get().isEnabled)
                {
                    component.get().Update();
                }
            }
        }

        static void AddComponent(IComponentBehaviour& component)
        {
            components.push_back(std::ref(component));
            component.Start();
            component.isEnabled = true;
        }
    };  
}