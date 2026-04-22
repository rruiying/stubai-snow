if(DEFINED ENV{VCPKG_ROOT} AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake"
        CACHE STRING "Vcpkg toolchain file")
endif()

cmake_minimum_required(VERSION 3.22)

project(stubai_snow
    VERSION 0.1.0
    DESCRIPTION "A simple snowy day redering of Stubai Gletscher Gamsgarten Bergstation"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(glfw3 CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)
find_package(fmt CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)

add_executable(stubai_snow
    src/app/main.cpp
    src/core/Window.cpp
    src/core/Logger.cpp
    src/core/Time.cpp
    src/core/Input.cpp
    src/gfx/GLContext.cpp
    src/gfx/Shader.cpp
    src/scene/Camera.cpp
)

target_link_libraries(stubai_snow
    PRIVATE
        glfw
        glad::glad
        spdlog::spdlog
        fmt::fmt
        glm::glm
)

target_include_directories(stubai_snow
    PRIVATE
        ${CMAKE_SOURCE_DIR}/src
)

target_compile_definitions(stubai_snow
    PRIVATE
        STUBAI_ASSETS_DIR="${CMAKE_SOURCE_DIR}/assets"
        GLM_FORCE_RADIANS
        GLM_FORCE_DEPTH_ZERO_TO_ONE
        GLM_ENABLE_EXPERIMENTAL
)

