#include <MxEngine.h>
#include <iostream>

using namespace MxEngine;

class YourScript : public Scriptable
{
public:
    virtual void OnCreate(MxObject& self) override 
    { 
        std::cout<<"--- Hello from script! ---"<<std::endl;
    }

    virtual void OnReload(MxObject& self) override 
    {
        std::cout<<"--- I'm reloaded! ---"<<std::endl;
    }
    virtual void OnUpdate(MxObject& self) override 
    { 
        Logger::LogLineToConsole("--- Script update! ---");
    }
};

MXENGINE_RUNTIME_EDITOR(YourScript);