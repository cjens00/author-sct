// =========================================================
// AUTHOR :: Authoritative Server Creation Tool ::
// (c) 2022 Cameron Jensen ::
// =========================================================
// [core/uiRenderer]
// =========================================================
// Notes:
// =========================================================
#include "core/ui/renderer.h"

Author::Core::UIRenderer::UIRenderer()
{
    this->shouldClose = false;
    this->window = nullptr;
}

bool Author::Core::UIRenderer::Init(const std::string &wTitle, IVec2 windowSize)
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

void Author::Core::UIRenderer::GLFWCallbackError(int ec, const char *desc)
{
    std::cout << std::format("GLFW Error {}: {}\r\n", ec, desc);
}

void Author::Core::UIRenderer::GLFWCallbackWindowPos(GLFWwindow *window, int x, int y)
{
    glfwSetWindowPos(window, x, y);
}

void Author::Core::UIRenderer::GLFWCallbackWindowSize(GLFWwindow *window, int w, int h)
{
    glfwSetWindowSize(window, w, h);
}

void Author::Core::UIRenderer::GLFWCallbackFBSize(GLFWwindow *window, int w, int h)
{
    glViewport(0, 0, w, h);
}

void Author::Core::UIRenderer::InstallCallbacks()
{
    glfwSetErrorCallback(GLFWCallbackError);
    glfwSetWindowSizeCallback(this->window, GLFWCallbackWindowSize);
    glfwSetWindowPosCallback(this->window, GLFWCallbackWindowPos);
    glfwSetFramebufferSizeCallback(this->window, GLFWCallbackFBSize);
}

GLFWwindow *Author::Core::UIRenderer::GetGLFWWindow()
{
    return this->window;
}

Author::Core::UIRenderer::~UIRenderer()
{
    glfwDestroyWindow(this->window);
    glfwTerminate();
}

void Author::Core::UIRenderer::Tick()
{
    this->shouldClose = glfwWindowShouldClose(this->window);
    glfwSwapBuffers(this->window);
    glfwPollEvents();
    glClearColor(0.65f,0.55f,0.55f,1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}