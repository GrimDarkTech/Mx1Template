# Mx1Template

Этот репозиторий содержит готовый к использованию шаблон проекта, в котором используется [MxEngine](https://github.com/asc-community/MxEngine). Вы можете отредактировать
`CMakeLists.txt", чтобы настроить все остальное под свои нужды. Ниже вы можете увидеть шаги, необходимые для создания проекта

### Установка
1. Склонируйте репозиторий
    ```bash
    git clone https://github.com/GrimDarkTech/Mx1Template
    ```
2. Перейдите в директорию проекта
    ```bash
    cd Mx1Template
    ```
2. Загрузите MxEngine
    ```bash
    git submodule update --init
    ```
3. Настройте сломанные зависимости в MxEngine\
    Перейдите в папку MxEngine
    ```bash
    cd MxEngine
    ```
    Замените в **.gitmodules** ссылку на модуль **assimp** (27 строка) с:
    ```
	url = https://github.com/MomoDeve/assimp
    ```
    на:
    ```
	url = https://github.com/assimp/assimp
    ```
4. Загрузите зависимости для MxEngine
    ```bash
    git subdmodule update --init
    ```
5. Отключите сборку примеров

    В директории **MxEngine** отредактируйте файл **CMakeLists.txt**:
    Замените:
    ```cmake
    if (MXENGINE_BUILD_SAMPLES)
        add_subdirectory(samples/SandboxApplication)
        add_subdirectory(samples/OfflineRendererSample)
        add_subdirectory(samples/PhysicsSample)
        add_subdirectory(samples/ProjectTemplate)
        add_subdirectory(samples/SoundSample)
        add_subdirectory(samples/VRCameraSample)
        add_subdirectory(samples/GrassSample)
        add_subdirectory(samples/Sponza)
        add_subdirectory(samples/PBR)
        add_subdirectory(samples/PathTracing)
        add_subdirectory(samples/Particles)
        add_subdirectory(samples/Doom)
    ```
    на:
    ```cmake
    if (MXENGINE_BUILD_SAMPLES)
    ```
6. Выполните сборку проекта, используя CMake
    ```cmake
    cmake --build . --config Debug
    ```

<p align="center">
<img src="preview.png">
</p>