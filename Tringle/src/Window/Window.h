#pragma once

#include <iostream>
#include <glad.h>
#include <glfw3.h>

class Window
{
public:
    Window(int width, int height, const char* title);
    Window();
    ~Window();
    void StartUp();
    void SwapBuffers();
    void ShutDown();

    void PollEvents();
    void FramebufferSizeCallback(int newWidth, int newHeight);
    bool isResizable = false;
    GLFWwindow* GetGLFWWindow();

private:
    GLFWwindow* mWindow;
    int mWidth, mHeight;
    const char* mTitle;
};