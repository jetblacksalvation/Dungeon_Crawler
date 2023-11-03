#include "Game.h"
GameWorld::GameWorld() {
    worldMessage = L"Loading World";
    //removes the cursor 
    CONSOLE_CURSOR_INFO     cursorInfo;
    GetConsoleCursorInfo(ConsoleOutputHandle, &cursorInfo);
    cursorInfo.bVisible = false; // set the cursor visibility
    SetConsoleCursorInfo(ConsoleOutputHandle, &cursorInfo);
};
void GameWorld::mainLoop() {
    int x = 0;
    INPUT_RECORD irec;
    LPDWORD a = (LPDWORD) new LPDWORD;
    while (true) {
        ReadConsoleInput(ConsoleInputHandle, &irec, 1, a);

        outWorldMessage();
        drawPlayer();
        //x++;
        if (irec.EventType == KEY_EVENT
            && ((KEY_EVENT_RECORD&)irec.Event).bKeyDown
            )//&& ! ((KEY_EVENT_RECORD&)irec.Event).wRepeatCount )
        {
            auto k = (KEY_EVENT_RECORD&)irec.Event;
            //std::cout << k.uChar.AsciiChar << "\n";
            if (k.uChar.AsciiChar == 'w') {

            }
            this->player.handleInput(k.uChar.AsciiChar);
        }

        //this->player.setDirection(Player::DIRECTIONS(x%4));
    }
}
void GameWorld::drawPlayer() {
    
    auto direction = this->player.getDirection();
    GameWorld::outputWideString(direction, player.PlayerCoordinates);
}
void GameWorld::outWorldMessage() {
    using namespace std::chrono;

    auto startTime = high_resolution_clock::now();
    SetCursor(NULL);
    while (true) {
        // Get the current time point
        auto currentTime = high_resolution_clock::now();

        // Calculate the elapsed time
        auto elapsedTime = duration_cast<duration<double>>(currentTime - startTime).count();

        //std::cout << elapsedTime << ": is time\n";
        // Check if the desired time has passed
        if (elapsedTime >= messageTime) {
            break;
        }
        outputWideString(this->worldMessage, 0, 0);
    }

};
//static functions------
int GameWorld::outputWideString(std::wstring c, int x, int y) {
    //returns number of characters drawn.
    LPDWORD a = (LPDWORD) new LPDWORD;

    for (SHORT index = 0; index < c.size(); index++) {
        _COORD cordinates = { x,y };

        cordinates.X += index;
        FillConsoleOutputCharacterW(ConsoleOutputHandle, c[index], 1, cordinates, a);
    }
    int ret = (int)a;

    delete a;
    return ret;
};
int GameWorld::outputWideString(std::wstring c, COORD pos) {
    //returns number of characters drawn.
    LPDWORD a = (LPDWORD) new LPDWORD;

    for (SHORT index = 0; index < c.size(); index++) {
        _COORD cordinates = pos;

        cordinates.X += index;
        FillConsoleOutputCharacterW(ConsoleOutputHandle, c[index], 1, cordinates, a);
    }
    int ret = (int)a;

    delete a;
    return ret;
};