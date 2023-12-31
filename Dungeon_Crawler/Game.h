#pragma once
#include <iostream>
#include <Windows.h>
#include <chrono>
#include "Player.h"
static HANDLE ConsoleOutputHandle = GetStdHandle(((DWORD)-11));
static HANDLE ConsoleInputHandle = GetStdHandle(STD_INPUT_HANDLE);
class GameWorld {
public:
    GameWorld();
    void outWorldMessage();
    void mainLoop();
    void drawPlayer();

    // STATIC FUNCTIONS BELOW------
    static int outputWideString(std::wstring c, int x, int y);
    static int outputWideString(std::wstring c, COORD pos);
private:
    Player player;

    std::wstring worldMessage = L"";
    clock_t bufferTime        = clock();
    double messageTime        = 1;
};
