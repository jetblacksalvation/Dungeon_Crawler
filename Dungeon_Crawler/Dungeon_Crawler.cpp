#include <iostream>
#include <Windows.h>
#include <chrono>
HANDLE ConsoleOutputHandle = GetStdHandle(((DWORD)-11));
HANDLE ConsoleInputHandle = GetStdHandle(STD_INPUT_HANDLE);
class GameWorld {
public:
    GameWorld() {
        worldMessage = L"Loading World";

    }
    void outWorldMessage(){
        using namespace std::chrono;

        auto startTime = high_resolution_clock::now();

        while (true) {
            // Get the current time point
            auto currentTime = high_resolution_clock::now();

            // Calculate the elapsed time
            auto elapsedTime = duration_cast<duration<double>>( currentTime- startTime ).count();

            //std::cout << elapsedTime << ": is time\n";
            // Check if the desired time has passed
            if (elapsedTime >= messageTime) {
                break;
            }
            outputWideString(this->worldMessage, 0, 0);
        }

    }
    //static because this is need not be bound to an instance of the class.
    static void outputWideString(std::wstring c, int x, int y) {
        LPDWORD a = (LPDWORD) new LPDWORD;

        for (SHORT index = 0; index < c.size(); index++) {
            _COORD cordinates = { x,y };

            cordinates.X += index;
            FillConsoleOutputCharacterA(ConsoleOutputHandle, c[index], 1, cordinates, a);
        }
        delete a;
    };
private:
    std::wstring worldMessage = L"";
    clock_t bufferTime        = clock();
    double messageTime        = 1;
};

int main()
{
    //std::wstring c = L"abcdef";
    //INPUT_RECORD irec;
    //LPDWORD a = (LPDWORD) new LPDWORD;
    auto game = GameWorld();

    game.outWorldMessage();
    //while (true) {
    //    outputWideString(c);

    //    ReadConsoleInput(ConsoleInputHandle, &irec, 1, a);
    //    if (irec.EventType == KEY_EVENT
    //        && ((KEY_EVENT_RECORD&)irec.Event).bKeyDown
    //        )//&& ! ((KEY_EVENT_RECORD&)irec.Event).wRepeatCount )
    //    {
    //        auto k = (KEY_EVENT_RECORD&)irec.Event;
    //        //std::cout << k.uChar.AsciiChar << "\n";
    //        c[0] = k.uChar.UnicodeChar;
    //    }

    //}



    //std::cout << "Hello Dungeon Crawler!\n";
}
