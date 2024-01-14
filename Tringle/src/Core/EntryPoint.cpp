#include "Application.h"

extern Tringle::Application* Tringle::CreateApplication();

int main(int argc, char *argv[])
{
    auto app = Tringle::CreateApplication();
    app->SetPath(argv);
    app->Run();

    return 0;
}