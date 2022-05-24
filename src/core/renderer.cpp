// =========================================================
// AUTHOR :: Authoritative Server Creation Tool ::
// (c) 2022 Cameron Jensen ::
// =========================================================
// [core/renderer]
// =========================================================
// Notes:
// =========================================================
#include "core/renderer.h"

Author::Core::Renderer::Renderer()
{
    this->shouldClose = false;
    this->window = nullptr;
}

bool Author::Core::Renderer::Init(const std::string &wTitle, IVec2 windowSize)
{
    if (!glfwInit()) return false;
    this->window = glfwCreateWindow(windowSize.x, windowSize.y, wTitle.c_str(), nullptr, nullptr);
    if (!this->window) return false;
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    InstallCallbacks();
    glfwMakeContextCurrent(this->window);
    glfwSwapInterval(1);
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
    {
        std::cerr << "Failed to initialize GLAD Loader.\r\n";
        return false;
    }
    return true;
}

void Author::Core::Renderer::GLFWCallbackError(int ec, const char *desc)
{
    std::cout << std::format("GLFW Error {}: {}\r\n", ec, desc);
}

void Author::Core::Renderer::GLFWCallbackWindowPos(GLFWwindow *window, int x, int y)
{
    glfwSetWindowPos(window, x, y);
}

void Author::Core::Renderer::GLFWCallbackWindowSize(GLFWwindow *window, int w, int h)
{
    glfwSetWindowSize(window, w, h);
}

void Author::Core::Renderer::GLFWCallbackFBSize(GLFWwindow *window, int w, int h)
{
    glViewport(0, 0, w, h);
}

void Author::Core::Renderer::InstallCallbacks()
{
    glfwSetErrorCallback(GLFWCallbackError);
    glfwSetWindowSizeCallback(this->window, GLFWCallbackWindowSize);
    glfwSetWindowPosCallback(this->window, GLFWCallbackWindowPos);
    glfwSetFramebufferSizeCallback(this->window, GLFWCallbackFBSize);
}

GLFWwindow *Author::Core::Renderer::GetGLFWWindow()
{
    return this->window;
}

Author::Core::Renderer::~Renderer()
{
    glfwDestroyWindow(this->window);
    glfwTerminate();
}

void Author::Core::Renderer::Tick()
{
    this->shouldClose = glfwWindowShouldClose(this->window);
    glfwSwapBuffers(this->window);
    glfwPollEvents();
    glClearColor(0.65f,0.55f,0.55f,1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

bool Author::Core::Renderer::ShouldClose()
{
    return this->shouldClose;
}



