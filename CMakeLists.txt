cmake_minimum_required(VERSION 3.18)
project(authorproj)
set(CMAKE_CXX_STANDARD 23)
add_link_options(/NODEFAULTLIB:msvcrt)

add_executable(
        author
        src/main.cpp
        src/core/ui/ui.cpp
        src/core/app_core.cpp
        src/core/ui/renderer.cpp
        lib/glad/src/glad.c
        lib/imgui/src/imgui.cpp
        lib/imgui/src/imgui_demo.cpp
        lib/imgui/src/imgui_draw.cpp
        lib/imgui/src/imgui_impl_glfw.cpp
        lib/imgui/src/imgui_impl_opengl3.cpp
        lib/imgui/src/imgui_tables.cpp
        lib/imgui/src/imgui_widgets.cpp
)

target_include_directories(
        author PUBLIC
        include
        lib/glfw
        lib/glad/include
        lib/imgui/include
        lib/libuv/include
        lib/json
)
target_link_libraries(author ${CMAKE_CURRENT_SOURCE_DIR}/lib/glfw/glfw3.lib)
target_link_libraries(author ${CMAKE_CURRENT_SOURCE_DIR}/lib/libuv/lib/uv.lib)