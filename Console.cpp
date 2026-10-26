#include "Console.h"
#include <iostream>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <cstdlib>

Console::Console() : name(""), currentLine(0), totalLine(0), timestamp(getCurrentTimestamp()) {}

Console::Console(std::string name, int currentLine, int totalLine)
    : name(name), currentLine(currentLine), totalLine(totalLine)
{
    timestamp = getCurrentTimestamp();
}

std::string Console::getCurrentTimestamp() {
    time_t now = time(nullptr);
    tm* localtm = localtime(&now);
    if (!localtm) {
        return "N/A";
    }
    char buffer[100];
    strftime(buffer, sizeof(buffer), "%m/%d/%Y, %I:%M:%S %p", localtm);
    return std::string(buffer);
}

void Console::display() const {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
    std::cout << "Console: " << name << std::endl;
    std::cout << "Instruction: " << currentLine << " / " << totalLine << std::endl;
    std::cout << "Started at: " << timestamp << std::endl;
}

void Console::display(int total) const {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
    std::cout << "Console: " << name << std::endl;
    std::cout << "Instruction: " << currentLine << " / " << total << std::endl;
    std::cout << "Started at: " << timestamp << std::endl;
}
