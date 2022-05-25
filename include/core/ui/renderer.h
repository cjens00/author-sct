#pragma once
// =========================================================
// AUTHOR :: Authoritative Server Creation Tool ::
// (c) 2022 Cameron Jensen ::
// =========================================================
// [core/uiRenderer]
// =========================================================
// Notes:
// =========================================================
// Standard library headers
#include <iostream>
#include <format>

// GLAD OpenGL Loader and GLFW Headers
#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "vec.h"

namespace Author::UI
{
    class Renderer
    {
        GLFWwindow *window;
    public:
        bool shouldClose;
    public:
        Renderer();
        ~Renderer();
        bool Init(const std::string &wTitle, IVec2 windowSize);
        GLFWwindow *GetGLFWWindow();
        void Tick();
        void SwapBuffer();
    private:
        void InstallCallbacks();
        static void GLFWCallbackError(int ec, const char *desc);
        static void GLFWCallbackWindowPos(GLFWwindow *window, int x, int y);
        static void GLFWCallbackWindowSize(GLFWwindow *window, int w, int h);
        static void GLFWCallbackFBSize(GLFWwindow *window, int w, int h);
    };
}