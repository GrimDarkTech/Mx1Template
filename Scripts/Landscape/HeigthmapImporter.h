#include <iostream>
#include <MxEngine.h>

using namespace MxEngine;

class HeigthmapImporter
{
    public:
    static void Import(Vector3 position, std::string path, float unitsPerPixel, float maxHeight)
    {   
        MxEngine::TextureHandle heightmap = AssetManager::LoadTexture(path.c_str());
        auto map = heightmap->GetRawTextureData();
        for(int x = 0; x < map.GetWidth(); x++)
        {
            for(int y = 0; y < map.GetHeight(); y++)
            {
                auto pixel = map.GetPixelFloat(x, y);
                float grey = (pixel[0] + pixel[1] + pixel[2]) / 3;

                auto cube = MxObject::Create();

                auto renderer = cube->AddComponent<MeshRenderer>();
                cube->AddComponent<MeshSource>(Primitives::CreateCube());
                cube->Transform.SetPosition(position + Vector3(x, (grey * 0.5), y) * unitsPerPixel);
                cube->Transform.SetScale(Vector3(1, grey * maxHeight, 1) * unitsPerPixel);

                if(grey > 0.75)
                    renderer->GetMaterial()->BaseColor = Vector3(0.5, 0.5, 0.5);
                else if(grey > 0.1 && grey <= 0.75)
                    renderer->GetMaterial()->BaseColor = Vector3(0.02, 0.3, 0.02);
                else if(grey > 0.08 && grey <= 0.1)
                    renderer->GetMaterial()->BaseColor = Vector3(0.9, 0.9, 0.05);
                else
                    renderer->GetMaterial()->BaseColor = Vector3(0, 0, 0.8);

                auto collider = cube->AddComponent<BoxCollider>();
                auto rigidBody = cube->AddComponent<RigidBody>();
                rigidBody->MakeStatic();
            }
        }
    }
};



