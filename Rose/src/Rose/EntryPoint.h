#pragma once

extern Rose::Application* Rose::CreateApplication();

int main(int argc, char** argv)
{
    auto app = Rose::CreateApplication();
    app->Run();
    delete app;
}