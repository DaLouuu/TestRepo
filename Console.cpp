#include "Console.h"
#include <iostream>
#include <ctime>
#include <iomanip>
#include <sstream>

Console::Console() : name(""), currentLine(0), totalLine(0), timestamp(getCurrentTimestamp()) {}

Console::Console(std::string name, int currentLine, int totalLine)
    : name(name), currentLine(currentLine), totalLine(totalLine)
{
    timestamp = getCurrentTimestamp();
}

std::string Console::getCurrentTimestamp() {
    time_t now = time(0);
    tm* localtm = localtime(&now);
    char buffer[100];
    strftime(buffer, sizeof(buffer), "%m/%d/%Y, %I:%M:%S %p", localtm);
    return std::string(buffer);
}

void Console::display(int totalLine) const {
    system("cls");
    std::cout << "Console: " << name << std::endl;
    std::cout << "Instruction: " << currentLine << " / " << totalLine << std::endl;
    std::cout << "Started at: " << timestamp << std::endl;
}
