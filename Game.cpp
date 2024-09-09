#include "Game.h"

Game::Game(): mWindow{nullptr}, mIsRunning{true}, mRenderer{nullptr} {
}

auto Game::Initialize() -> bool {
    if (const int sdlResult = SDL_Init(SDL_INIT_VIDEO); sdlResult != 0) {
        SDL_Log("SDLを初期化できません: %s", SDL_GetError());
        return false;
    }

    mWindow = SDL_CreateWindow("ゲームプログラミングC++(第1章)", 100, 100, 1024,
                               768, 0);
    if (!mWindow) {
        SDL_Log("ウィンドウの作成に失敗しました:%s", SDL_GetError());
        return false;
    }

    mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED |
                                                  SDL_RENDERER_PRESENTVSYNC);
    if (!mRenderer) {
        SDL_Log("レンダラの作成に失敗しました:%s", SDL_GetError());
        return false;
    }

    return true;
}

auto Game::Shutdown() const -> void {
    SDL_DestroyRenderer(mRenderer);
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
            default: ;
        }
    }
    // キーボードの状態を取得する
    const auto state = SDL_GetKeyboardState(nullptr);
    // [ESC] キーが押された時も、ループを終える
    if (state[SDL_SCANCODE_ESCAPE]) {
        mIsRunning = false;
    }
}
auto Game::UpdateGame() -> void { return; }
auto Game::GenerateOutput() -> void {
    SDL_SetRenderDrawColor(mRenderer, 0, 0, 255, 255);
    SDL_RenderClear(mRenderer);
    // ゲームシーン全体の描画
   SDL_RenderPresent(mRenderer);
}
