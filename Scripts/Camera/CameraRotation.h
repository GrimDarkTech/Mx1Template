#include <iostream>
#include <MxEngine.h>

using namespace MxEngine;

class CameraRotation
{
    private:
    InputController::Handle _controller;
    bool isBindRotation = true;

    public:
    CameraRotation()
    {
    }

    void SetInputController(InputController::Handle controller)
    {
        _controller = controller;
    }


    void SwitchRotationMode()
    {
        if(isBindRotation)
        {
            isBindRotation = false;

            _controller->UnbindAll();

		    Input::SetCursorMode(MxEngine::CursorMode::NORMAL);

        }
        else
        {
            isBindRotation = true;
            _controller->BindRotation();

			Input::SetCursorMode(MxEngine::CursorMode::DISABLED);

        }
        _controller->BindMovement(KeyCode::W, KeyCode::A, KeyCode::S, KeyCode::D, KeyCode::SPACE, KeyCode::LEFT_SHIFT);
    }
};