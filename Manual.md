# Как пользоваться проектом

# Как передать точку в NavigationAgent

У экземляра класса NavigationAgent вызовите метод ```AddRoutePosition(Vector position)```:
```C++
    Vector3 point = Vector3(1, 3, 0);
    _agent.AddRoutePosition(hitPoint);
```

## Как передать точку, в которой находится камера

В **MxApplication.cpp** найдите метод **OnUpdate()** и измените код, выполняемый при работе условного оператора ```if (Input::IsMousePressed(MouseButton::LEFT))```, обрабатывающего нажатие левой кнопки мыши.

Результат, должен выглядеть следующим образом:
```C++
    if (Input::IsMousePressed(MouseButton::LEFT)) 
    {
        Vector3 position = cameraObject->Transform.GetPosition();
        Marker::CreateMarker(position, Vector3(0.05, 0.05, 0.05), Vector3(1, 0, 0));
        _agent.AddRoutePosition(position);
    }
```

## Как передать точку, в которую направлен центр экрана

В **MxApplication.cpp** найдите метод **OnUpdate()** и измените код, выполняемый при работе условного оператора ```if (Input::IsMousePressed(MouseButton::LEFT))```, обрабатывающего нажатие левой кнопки мыши.

Результат, должен выглядеть следующим образом:
```C++
    if (Input::IsMousePressed(MouseButton::LEFT)) 
    {
        Vector3 position = cameraObject->Transform.GetPosition();

        auto camera = cameraObject->GetComponent<CameraController>();;
        auto hit = Raycaster::Raycast(position, camera->GetDirection(), 20);

        auto hitObject = std::get<0>(hit);
        auto hitPoint = std::get<1>(hit);
        auto hitDistance = std::get<2>(hit);

        if(hitObject.IsValid())
        {
            Marker::CreateMarker(hitPoint, Vector3(0.05, 0.05, 0.05), Vector3(1, 0, 0));
            _agent.AddRoutePosition(hitPoint);
        }
    }
```