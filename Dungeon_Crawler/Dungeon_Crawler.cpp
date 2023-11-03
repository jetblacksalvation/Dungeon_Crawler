#include "Game.h"

int main()
{
    //std::wstring c = L"abcdef";
    //INPUT_RECORD irec; → ← ↑ ↓ ↕ ↨ ↔  
    //LPDWORD a = (LPDWORD) new LPDWORD;
    auto game = GameWorld();

    game.mainLoop();
    //while (true) {
    //    outputWideString(c);



    //}



    //std::cout << "Hello Dungeon Crawler!\n";
}
