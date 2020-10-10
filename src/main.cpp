#include <SDL2/SDL.h>
#include <memory>
#include "Engine/Engine.hpp"
#include <iostream>
#include "TestScene.hpp"

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[])
{
    sgf::Engine::CreateWindow(sgf::Resolution::R_720P, "Super Cool Game");
    sgf::Engine::OpenScene<TestScene>();
    sgf::Engine::CloseWindow();

    return 0;
}