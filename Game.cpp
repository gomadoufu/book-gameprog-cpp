#include "Game.h"

Game::Game() {
    mWindow = nullptr;
    mIsRunning = true;
}

auto Game::Initialize() -> bool { auto sdlResult = SDL_Init(SDL_INIT_VIDEO); }
