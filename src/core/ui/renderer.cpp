// =========================================================
// AUTHOR :: Authoritative Server Creation Tool ::
// (c) 2022 Cameron Jensen ::
// =========================================================
// [core/Renderer]
// =========================================================
// Notes:
// =========================================================
#include "core/ui/renderer.h"

Author::UI::Renderer::Renderer()
{
    this->shouldClose = false;
    this->window = nullptr;
}

bool Author::UI::Renderer::Init(const std::string &wTitle, IVec2 windowSize)
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

void Author::UI::Renderer::GLFWCallbackError(int ec, const char *desc)
{
    std::cout << std::format("GLFW Error {}: {}\r\n", ec, desc);
}

void Author::UI::Renderer::GLFWCallbackWindowPos(GLFWwindow *window, int x, int y)
{
    glfwSetWindowPos(window, x, y);
}

void Author::UI::Renderer::GLFWCallbackWindowSize(GLFWwindow *window, int w, int h)
{
    glfwSetWindowSize(window, w, h);
}

void Author::UI::Renderer::GLFWCallbackFBSize(GLFWwindow *window, int w, int h)
{
    glViewport(0, 0, w, h);
}

void Author::UI::Renderer::InstallCallbacks()
{
    glfwSetErrorCallback(GLFWCallbackError);
    glfwSetWindowSizeCallback(this->window, GLFWCallbackWindowSize);
    glfwSetWindowPosCallback(this->window, GLFWCallbackWindowPos);
    glfwSetFramebufferSizeCallback(this->window, GLFWCallbackFBSize);
}

GLFWwindow *Author::UI::Renderer::GetGLFWWindow()
{
    return this->window;
}

Author::UI::Renderer::~Renderer()
{
    glfwDestroyWindow(this->window);
    glfwTerminate();
}

void Author::UI::Renderer::Tick()
{
    this->shouldClose = glfwWindowShouldClose(this->window);
    glfwPollEvents();
    glClearColor(0.65f, 0.55f, 0.55f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

void Author::UI::Renderer::SwapBuffer()
{
    glfwSwapBuffers(this->window);
}

