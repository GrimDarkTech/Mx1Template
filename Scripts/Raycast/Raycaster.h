#include <iostream>
#include <MxEngine.h>

using namespace MxEngine;

class Raycaster
{
    public:
    bool isMoving;

    Raycaster()
    {
    }

    static std::tuple<MxObject::Handle, Vector3, float> Raycast(Vector3& from, Vector3& direction, float distance)
    {
        float fraction = 0;
        auto hitResult = Physics::RayCast(from, from + direction * distance, fraction);
        Vector3 hitPoint = Vector3(0, 0, 0);
        
        if(hitResult.IsValid())
        {
            std::cout << "Fraction: " << fraction << std::endl;

            if (fraction < 1)
            {	
                Logger::Log(VerbosityType::INFO, "Raycast done!");
                hitPoint = from + direction * distance * fraction;
                std::cout << "HitPoint: (" << hitPoint.x << ", " << hitPoint.y << ", " << hitPoint.z << ")" << std::endl;
            }

        }

        std::tuple<MxObject::Handle, Vector3, float> result(hitResult, hitPoint, fraction);
        
        return result;
    }

     


    


};