#pragma once

extern Rose::Application* Rose::CreateApplication();

int main(int argc, char** argv)
{
    Rose::Log::Init();
    ROSE_CORE_WARN("Testing log macro");
    auto app = Rose::CreateApplication();
    app->Run();
    delete app;
}