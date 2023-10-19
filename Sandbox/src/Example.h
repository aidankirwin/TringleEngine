#pragma once

#include "Tringle.h"

class ExampleGame : public Tringle::Application
{
public:
    ExampleGame() {}
    ~ExampleGame() {}

    virtual void StartUp();
    virtual void Update();
    virtual void ShutDown();
};

Tringle::Application* Tringle::CreateApplication()
{
    return new ExampleGame();
}