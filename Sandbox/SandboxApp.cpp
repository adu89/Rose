#include <Rose.h>

#include <string>
#include <iostream>

class SandboxApp : public Rose::Application
{
public:
    SandboxApp()
    {
    }
    ~SandboxApp()
    {
    }
};

Rose::Application* Rose::CreateApplication()
{
    return new SandboxApp();
}