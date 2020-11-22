#include <SDL2/SDL.h>
#include "SGF/Core.hpp"
#include "TestScene.hpp"

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[])
{
    sgf::Window::Create(sgf::R_720P, "igra");
    sgf::Engine::OpenScene<TestScene>();
    sgf::Window::Close();

    return 0;
}