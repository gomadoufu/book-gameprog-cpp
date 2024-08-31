## 書籍 ゲームプログラミングC++

現時点でのビルドスクリプト  
`g+++ Main.cpp Game.cpp -IExternal/SDL/include -D_THREAD_SAFE -lSDL2-2.0.0 -Wl,-rpath,External/SDL/lib/mac -o main`
