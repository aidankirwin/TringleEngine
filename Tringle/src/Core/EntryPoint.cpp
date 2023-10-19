#include "Application.h"

extern Tringle::Application* Tringle::CreateApplication();

int main()
{
    auto app = Tringle::CreateApplication();
    app->Run();

    return 0;
}