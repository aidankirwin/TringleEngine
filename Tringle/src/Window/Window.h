#pragma once

#include <iostream>
#include <glad.h>

#ifdef _WIN32
    #include <glfw3.h>
#endif

#ifdef __APPLE__
    #define GL_SILENCE_DEPRECATION
    #include <glfw3.h>
#endif

class Window
{
public:
    Window(int width, int height, const char* title);
    Window();
    ~Window();
    void StartUp();
    void Update();
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