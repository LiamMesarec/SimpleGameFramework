cmake_minimum_required(VERSION 3.14...3.20)

project(
    SimpleGameFramework
    VERSION 1.0
    DESCRIPTION "A game engine for developing 2D games."
    LANGUAGES CXX
)

include(FindGit)

find_package(Git)
if(NOT Git_FOUND)
    message(FATAL_ERROR "Git not found! Download from: https://git-scm.com/downloads")
endif()

include(FetchContent)

FetchContent_Declare(
    SDL2
    GIT_REPOSITORY https://github.com/libsdl-org/SDL
    GIT_TAG release-2.24.1
    SOURCE_DIR SDL2
)

FetchContent_Declare(
    SDL2_IMAGE
    GIT_REPOSITORY https://github.com/libsdl-org/SDL_image
    GIT_TAG release-2.6.2
    SOURCE_DIR SDL2_IMAGE
)

FetchContent_Declare(
    SDL2_TTF
    GIT_REPOSITORY  https://github.com/libsdl-org/SDL_ttf
    GIT_TAG main
    SOURCE_DIR SDL2_TTF
)

FetchContent_Declare(
    SDL2_MIXER
    GIT_REPOSITORY https://github.com/libsdl-org/SDL_mixer
    GIT_TAG main
    SOURCE_DIR SDL2_MIXER
)

FetchContent_MakeAvailable(SDL2 SDL2_IMAGE SDL2_TTF SDL2_MIXER)

add_library(${PROJECT_NAME}
    src/math/Random.cpp
    src/input/Keyboard.cpp
    src/input/Mouse.cpp
    src/gui/Texture.cpp
    src/gui/Grid.cpp
    src/gui/Text.cpp
    src/gui/Polygon.cpp
    src/engine/EventManager.cpp
    src/engine/Time.cpp
    src/engine/ObjectManager.cpp
    src/engine/Camera.cpp
    src/engine/SceneManager.cpp
    src/engine/Error.cpp
    src/engine/Window.cpp
    src/engine/ObjectCollision.cpp
    src/engine/Audio.cpp
)

target_include_directories(${PROJECT_NAME} SYSTEM PRIVATE
    ${CMAKE_BINARY_DIR}/SDL2
    ${CMAKE_BINARY_DIR}/SDL2_IMAGE
    ${CMAKE_BINARY_DIR}/SDL2_MIXER
    ${CMAKE_BINARY_DIR}/SDL2_TTF
)

target_link_libraries(${PROJECT_NAME} PRIVATE ${SDL2_LIBRARIES} SDL2_image SDL2_mixer SDL2_ttf)

target_include_directories(${PROJECT_NAME} PRIVATE include)
target_include_directories(${PROJECT_NAME} PRIVATE src)

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_20)
set_target_properties(${PROJECT_NAME} PROPERTIES CXX_EXTENSIONS OFF VERSION ${PROJECT_VERSION})

set(CMAKE_SHARED_LINKER_FLAGS "-fPIC")

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR "clang")
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic)
endif()
if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    target_compile_options(${PROJECT_NAME} PRIVATE /W4)
endif()
