#include "SDL/SDL.h"

class Game {
   public:
    Game();
    // ゲームを初期化する
    auto Initialize() -> bool;
    auto RunLoop() -> void;
    // ゲームをシャットダウンする
    auto Shutdown() -> void;

   private:
    // ゲームループのためのヘルパー関数群
    auto ProcessInput() -> void;
    auto UpdateGame() -> void;
    auto GenerateOutput() -> void;

    // SDLが作るウィンドウ
    SDL_Window* mWindow;
    // ゲームの続行を支持する
    bool mIsRunning;
};
