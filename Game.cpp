#include "Game.h"

#include <complex>

Game::Game(): mWindow{nullptr}, mIsRunning{true}, mRenderer{nullptr}, mTicksCount{0}, mPaddlePos{15.0f, 768.0f / 2.0f},
              mPaddleDir{0}, mBallPos{1024.0f / 2.0f, 768.0f / 2.0f}, mBallVel{-200.0f, 235.0f} {
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
    SDL_Event event{};
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
    // パドルの移動
    mPaddleDir = 0;
    if (state[SDL_SCANCODE_W]) {
        mPaddleDir -= 1;
    }
    if (state[SDL_SCANCODE_S]) {
        mPaddleDir += 1;
    }
}
auto Game::UpdateGame() -> void {
    // 前のフレームから16msが経過するまで待つ
    while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16)) {
        ;
    }

    // deltatime は前のフレームとの時刻の差を秒に変換した値
    auto deltatime = static_cast<float>(SDL_GetTicks() - mTicksCount) / 1000.0f;

    // deltatime を最大値で制限する
    if (deltatime > 0.05f) {
        deltatime = 0.05f;
    }
    // 時刻を更新 (次のフレームのために)
    mTicksCount = SDL_GetTicks();

    // ゲームオーバーの判定
    if (mBallPos.x <= 0) {
        mIsRunning = false;
    }

    // ゲームワールドのオブジェクトを、deltatime に基づいて更新する
    // パドルの移動
    if (mPaddleDir != 0) {
        mPaddlePos.y += static_cast<float>(mPaddleDir) * 300.0f * deltatime;
        // パドルが画面外に出ないようにする
        if (mPaddlePos.y < (paddleH / 2.0f + thickness)) {
            mPaddlePos.y = paddleH / 2.0f + thickness;
        } else if (mPaddlePos.y > (768.0f - paddleH / 2.0f - thickness)) {
            mPaddlePos.y = 768.0f - paddleH / 2.0f - thickness;
        }
    }
    // ボールの移動
    mBallPos.x += mBallVel.x * deltatime;
    mBallPos.y += mBallVel.y * deltatime;
    if (mBallPos.y <= thickness && mBallVel.y < 0.0f) {
        mBallVel.y *= -1;
    }
    if (mBallPos.y >= (768 - thickness) && mBallVel.y > 0.0f) {
        mBallVel.y *= -1;
    }
    if (mBallPos.x >= (1024 - thickness) && mBallVel.x > 0.0f) {
        mBallVel.x *= -1;
    }
    if (const auto diff = std::abs(mPaddlePos.y - mBallPos.y);
        diff <= paddleH / 2.0f && mBallPos.x <= 25.0f && mBallPos.x >= 20.0f && mBallVel.x < 0.0f) {
        mBallVel.x *= -1.0f;
    }
}

auto Game::DrawScene() const -> void {
    SDL_SetRenderDrawColor(mRenderer, 255, 255, 255, 255);
    constexpr SDL_Rect upper_wall{
        0, 0, 1024, thickness
    };
    SDL_RenderFillRect(mRenderer, &upper_wall);
    constexpr SDL_Rect lower_wall{
        0, 768 - thickness, 1024, thickness
    };
    SDL_RenderFillRect(mRenderer, &lower_wall);
    constexpr SDL_Rect right_wall{
        1010, 0, thickness, 768
    };
    SDL_RenderFillRect(mRenderer, &right_wall);
    const SDL_Rect paddle{
        static_cast<int>(mPaddlePos.x - 15 / 2.0f),
        static_cast<int>(mPaddlePos.y - paddleH / 2.0f),
        15, paddleH
    };
    SDL_RenderFillRect(mRenderer, &paddle);
    const SDL_Rect ball{
        static_cast<int>(mBallPos.x - 15 / 2.0f),
        static_cast<int>(mBallPos.y - 15 / 2.0f),
        15, 15
    };
    SDL_RenderFillRect(mRenderer, &ball);
}

auto Game::GenerateOutput() const -> void {
    SDL_SetRenderDrawColor(mRenderer, 0, 0, 255, 255);
    SDL_RenderClear(mRenderer);
    // ゲームシーン全体の描画
    Game::DrawScene();
   SDL_RenderPresent(mRenderer);
}
