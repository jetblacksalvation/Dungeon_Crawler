#include <iostream>
#include <Windows.h>
#include <ctime>
auto ConsoleOutputHandle = GetStdHandle(((DWORD)-11));
HANDLE ConsoleInputHandle = GetStdHandle(STD_INPUT_HANDLE);

void outputWideString(std::wstring c) {
    _COORD cordinates = { 0,0 };
    LPDWORD a = (LPDWORD) new LPDWORD;

    for (SHORT index = cordinates.X; index < c.size(); index++) {
        cordinates.X = index;
        FillConsoleOutputCharacterA(ConsoleOutputHandle, c[index], 1, cordinates, a);
    }
    delete a;
}
int main()
{
    std::wstring c = L"abcdef";
    INPUT_RECORD irec;
    LPDWORD a = (LPDWORD) new LPDWORD;

    while (true) {
        outputWideString(c);

        ReadConsoleInput(ConsoleInputHandle, &irec, 1, a);
        if (irec.EventType == KEY_EVENT
            && ((KEY_EVENT_RECORD&)irec.Event).bKeyDown
            )//&& ! ((KEY_EVENT_RECORD&)irec.Event).wRepeatCount )
        {
            auto k = (KEY_EVENT_RECORD&)irec.Event;
            //std::cout << k.uChar.AsciiChar << "\n";
            c[0] = k.uChar.UnicodeChar;
        }

    }



    //std::cout << "Hello Dungeon Crawler!\n";
}
