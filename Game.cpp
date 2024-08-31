#include "Game.h"

Game::Game() {
    mWindow = nullptr;
    mIsRunning = true;
}

auto Game::Initialize() -> bool {
    int sdlResult = SDL_Init(SDL_INIT_VIDEO);
    if (sdlResult != 0) {
        SDL_Log("SDLを初期化できません: %s", SDL_GetError());
        return false;
    }

    mWindow = SDL_CreateWindow("ゲームプログラミングC++(第1章)", 100, 100, 1024,
                               768, 0);
    if (!mWindow) {
        SDL_Log("ウィンドウの作成に失敗しました:%s", SDL_GetError());
        return false;
    }
    return true;
}

auto Game::Shutdown() -> void {
    SDL_DestroyWindow(mWindow);
    SDL_Quit();
}

auto Game::RunLoop() -> void {
    while (mIsRunning) {
        ProcessInput();
        UpdateGame();
        GenerateOutput();
    }
}

auto Game::ProcessInput() -> void {
    SDL_Event event;
    // キューにイベントがあれば繰り返す
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            // SDL_QUIT イベントならば、ループを終える
            case SDL_QUIT:
                mIsRunning = false;
                break;
        }
    }
    // キーボードの状態を取得する
    const auto state = SDL_GetKeyboardState(NULL);
    // [ESC] キーが押された時も、ループを終える
    if (state[SDL_SCANCODE_ESCAPE]) {
        mIsRunning = false;
    }
}
auto Game::UpdateGame() -> void { return; }
auto Game::GenerateOutput() -> void { return; }
