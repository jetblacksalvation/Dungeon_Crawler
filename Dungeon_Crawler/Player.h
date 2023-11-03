#pragma once
#include <iostream>
#include <string>
#include <Windows.h>
class Player
{
public:
	enum class DIRECTIONS:int {
		
		LEFT = 0,
		RIGHT = 1,
		UP = 2,
		DOWN = 3
	};
	Player() {
		CONSOLE_SCREEN_BUFFER_INFO csbi;

		GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
		this->PlayerCoordinates = { static_cast<SHORT>((csbi.srWindow.Right - csbi.srWindow.Left + 1) / 2), static_cast<SHORT>((csbi.srWindow.Bottom - csbi.srWindow.Top + 1) / 2) };
		//std::cout << PlayerCoordinates.X << ": x \n";
		//std::cout << PlayerCoordinates.X << ": y \n";
		//std::cout << PlayerCoordinates.X << ": x \n";

	}
	void setDirection(DIRECTIONS dir) {
		internalDirection = dir;
	}
	std::wstring getDirection() {
		std::wstring ret;
		ret += charDirections[static_cast<int>(internalDirection)];
		return ret;
	}
	void handleInput(char value) {
		if (value == 'w')
			PlayerCoordinates.Y += 1;
		if (value == 's')
			PlayerCoordinates.Y -= 1;
		if (value == 'a')
			PlayerCoordinates.X -= 1;
		if (value == 'd')
			PlayerCoordinates.X += 1;
	}
	COORD PlayerCoordinates = { 0,0 };

private:
	DIRECTIONS internalDirection = DIRECTIONS::UP;
	std::wstring charDirections{ L"←→↑↓" };
};

