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

    // GLFW user pointer for callbacks
    // Stores address of instance handling mWindow to forward to callbacks
    glfwSetWindowUserPointer(mWindow, reinterpret_cast<void*>(this));

    // TODO: make this conditional for resizable windows only
    auto framebufferCallback = [](GLFWwindow* glfwWindow, int width, int height)
    {
        Window* window = static_cast<Window*>(glfwGetWindowUserPointer(glfwWindow));
        window->FramebufferSizeCallback(width, height);
    };

    // TODO: test once drawcalls are setup
    // glfwSetFramebufferSizeCallback(mWindow, framebufferCallback);


    // TODO: need to close window when 'X' is hit
    // This could be done by following same callback setup and calling some InputManager class
}

void Window::PollEvents()
{
    glfwMakeContextCurrent(mWindow);
    glfwPollEvents();
}

void Window::Update()
{
    glClearColor(0.1f, 0.3f, 0.5f, 1.0f); // TODO: remove placeholder
    glClear(GL_COLOR_BUFFER_BIT);

    glfwSwapBuffers(mWindow);
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