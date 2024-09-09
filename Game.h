#ifndef GAME_H
#define GAME_H
#include "SDL/SDL.h"

class Game {
    // SDLが作るウィンドウ
    SDL_Window* mWindow;
    // ゲームの続行を支持する
    bool mIsRunning;
    // 2D描画を行うためのレンダラ
    SDL_Renderer* mRenderer;

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
    auto GenerateOutput() -> void;

};
#endif // GAME_H
