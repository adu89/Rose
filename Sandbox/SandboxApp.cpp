#include <Rose.h>

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