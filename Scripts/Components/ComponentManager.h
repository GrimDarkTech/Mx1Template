#include <MxEngine.h>
#include <functional>
#include <vector>

#include "IComponentBehaviour.h"

namespace ComponentSystem
{
    class ComponentManager
    {
        public:
        static inline std::vector<std::reference_wrapper<ComponentSystem::IComponentBehaviour>> components;

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