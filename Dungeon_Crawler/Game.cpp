#include "Game.h"
std::mutex myMutex;

void InputThread(GameWorld * t) {
    while (true) {
        std::lock_guard<std::mutex> Lock(myMutex);

        if (_kbhit()) {
            t->player.handleInput(_getch());
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
}
GameWorld::GameWorld() {
    worldMessage = L"Loading World";
    //removes the cursor 
    CONSOLE_CURSOR_INFO     cursorInfo;
    GetConsoleCursorInfo(ConsoleOutputHandle, &cursorInfo);
    cursorInfo.bVisible = false; // set the cursor visibility
    SetConsoleCursorInfo(ConsoleOutputHandle, &cursorInfo);
    DWORD dwMode;

    GetConsoleMode(ConsoleInputHandle, &dwMode);
    SetConsoleMode(ConsoleInputHandle, dwMode | ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT);

    this->playerInputThread = std::thread(&InputThread,this);

};
void GameWorld::mainLoop() {

    while (true) {
        outWorldMessage();
        drawPlayer();

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
