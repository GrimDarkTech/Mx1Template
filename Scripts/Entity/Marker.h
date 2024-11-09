#include <iostream>
#include <MxEngine.h>

using namespace MxEngine;

class Marker
{
    public:
    static void CreateMarker(Vector3 position, Vector3 scale, Vector3 color)
    {   
        auto sphere = MxObject::Create();

        sphere->Transform.SetPosition(position);
        sphere->Transform.SetScale(scale);
        auto renderer = sphere->AddComponent<MeshRenderer>();
        sphere->AddComponent<MeshSource>(Primitives::CreateSphere());

        renderer->GetMaterial()->BaseColor = color;
    }
};



