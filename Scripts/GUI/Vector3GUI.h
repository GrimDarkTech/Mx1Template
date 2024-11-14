#include <iostream>
#include <MxEngine.h>

using namespace MxEngine;

class Vector3GUI
{
    public:
    static void DrawGUI(Vector3 vector, std::string label)
    {
        ImGui::Begin(label.c_str());
        ImGui::InputFloat("X: ", &vector.x);
        ImGui::InputFloat("Y: ", &vector.y);
        ImGui::InputFloat("Z: ", &vector.z);
        ImGui::End();
    }

    static void DrawGUILabels(Vector3 vector, std::string label, std::string xLabel, std::string yLabel, std::string zLabel)
    {
        ImGui::Begin(label.c_str());
        ImGui::InputFloat(xLabel.c_str() , &vector.x);
        ImGui::InputFloat(yLabel.c_str(), &vector.y);
        ImGui::InputFloat(zLabel.c_str(), &vector.z);
        ImGui::End();
    }

    static void DrawGUIReference(Vector3& vector, std::string label)
    {
        ImGui::Begin(label.c_str());
        ImGui::InputFloat("X: ", &vector.x);
        ImGui::InputFloat("Y: ", &vector.y);
        ImGui::InputFloat("Z: ", &vector.z);
        ImGui::End();
    }
};