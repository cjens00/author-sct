cmake_minimum_required(VERSION 3.18)
project(author-proj LANGUAGES C CXX)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_C_STANDARD 11)

# This prevents Windows from loading in default GL headers
if(WIN32)
add_link_options(/NODEFAULTLIB:msvcrt)
endif()

add_executable(
        author
        src/main.cpp
        src/core/app_core.cpp
        src/core/Server.cpp
        src/core/ui/console.cpp
        src/core/ui/ui.cpp
        src/core/ui/renderer.cpp
        lib/glad/src/glad.c
        lib/imgui/src/imgui.cpp
        lib/imgui/src/imgui_demo.cpp
        lib/imgui/src/imgui_draw.cpp
        lib/imgui/src/imgui_impl_glfw.cpp
        lib/imgui/src/imgui_impl_opengl3.cpp
        lib/imgui/src/imgui_tables.cpp
        lib/imgui/src/imgui_widgets.cpp
        include/rev2/helper/iobserver.cpp include/rev2/helper/IObserver.h src/rev2/net/Server.cpp src/rev2/net/server.h src/rev2/net/ISocket.cpp src/rev2/net/INetClient.h)

target_include_directories(
        author PUBLIC
        include
        lib/glfw
        lib/glad/include
        lib/imgui/include
        lib/libuv
        lib/json
)

# Required for libuv
if(WIN32)
    target_link_libraries(author wsock32 ws2_32 iphlpapi userenv)
    # Saving for later in case of linker errors with libuv deps
    # target_link_libraries(author psapi)
endif()

target_link_libraries(author ${CMAKE_CURRENT_SOURCE_DIR}/lib/libuv/uv_a.lib)
target_link_libraries(author ${CMAKE_CURRENT_SOURCE_DIR}/lib/glfw/glfw3.lib)

