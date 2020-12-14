#include <SDL2/SDL.h>
#include "../../include/SGF/Core.hpp"
#include "TicTacToeScene.hpp"

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[])
{
    sgf::Window::Create(sgf::R_720P, "TicTacToe");
    sgf::Engine::OpenScene<TicTacToe>();

    return 0;
}