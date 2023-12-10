#include "Window.h"

Window::Window(int width, int height, const char* title)
{
    mWidth = width;
    mHeight = height;
    mTitle = title;
}

Window::~Window()
{
}

void Window::StartUp()
{
    // Initialize GLFW
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    #ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif

    // Create window
    mWindow = glfwCreateWindow(mWidth, mHeight, mTitle, NULL, NULL);

    // Error check
    if (mWindow == NULL) 
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        exit(-1);
    }

    glfwMakeContextCurrent(mWindow);



    // Error check.
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) 
    {
		std::cout << "Failed to initialize GLAD" << std::endl;
		exit(-1);
	}

    glViewport(0, 0, mWidth, mHeight);

    glEnable(GL_DEPTH_TEST);
}

void Window::StartRender()
{
    glClearColor(0.1f, 0.3f, 0.5f, 1.0f); // TODO: remove placeholder
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::SwapBuffersAndPollEvents()
{
    glfwSwapBuffers(mWindow);
    glfwPollEvents();
}

void Window::ShutDown()
{
    glfwTerminate();
}

void Window::FramebufferSizeCallback(int newWidth, int newHeight)
{
    mWidth = newWidth;
    mHeight = newHeight;
    glViewport(0, 0, mWidth, mHeight);
}

GLFWwindow* Window::GetGLFWWindow()
{
    return mWindow;
}