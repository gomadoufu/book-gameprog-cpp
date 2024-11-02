#ifndef GAME_H
#define GAME_H
#include "SDL/SDL.h"


constexpr int thickness = 15;
constexpr int paddleH = 100;

struct Vector2 {
    float x;
    float y;
};

class Game {
    // SDLが作るウィンドウ
    SDL_Window* mWindow;
    // ゲームの続行を支持する
    bool mIsRunning;
    // 2D描画を行うためのレンダラ
    SDL_Renderer* mRenderer;
    // ゲームループのための変数
    uint32_t mTicksCount;

    Vector2 mPaddlePos;
    int8_t mPaddleDir;

    Vector2 mBallPos;
    Vector2 mBallVel;

public:
    Game();
    // ゲームを初期化する
    auto Initialize() -> bool;
    auto RunLoop() -> void;
    // ゲームをシャットダウンする
    auto Shutdown() const -> void;

   private:
    // ゲームループのためのヘルパー関数群
    auto ProcessInput() -> void;

    auto UpdateGame() -> void;
    auto DrawScene() const -> void;
    auto GenerateOutput() const -> void;

};

#endif // GAME_H
