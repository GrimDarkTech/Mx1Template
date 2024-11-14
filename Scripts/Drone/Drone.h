
using namespace MxEngine;

class UAV
{
    private:
    MxObject::Handle gameObject;

    public:
    UAV()
    {
    }

    void Start(MxEngine::MxObject::Handle gameObject, std::string modelName)
    {
        this->gameObject = gameObject;
        this->gameObject->Name = "Drone";

        auto mesh = this->gameObject->AddComponent<MeshSource>(AssetManager::LoadMesh(("Models/" + modelName).c_str()));
        TransformComponent meshTransform;
        meshTransform.SetRotation(Vector3(90, 0, -90));
        mesh->Mesh->GetSubMeshByIndex(0).SetTransform(meshTransform);
        auto renderer = this->gameObject->AddComponent<MeshRenderer>();

        renderer->GetMaterial()->AlbedoMap = AssetManager::LoadTexture("Models/Drone_DefaultMaterial_BaseColor.png");
        this->gameObject->Transform.SetRotation({ 0, 0.0f, 0.0f });
        this->gameObject->Transform.SetScale({ 0.5f, 0.5f, 0.5f });

        auto material = renderer->GetMaterial();
    }

    void ReloadModel(std::string modelName)
    {
        auto loaded = AssetManager::LoadMesh(("Models/" + modelName).c_str());
        if(loaded.IsValid())
        {
                    auto mesh = this->gameObject->GetComponent<MeshSource>();
                    mesh->Mesh = loaded;
        }
    }
};