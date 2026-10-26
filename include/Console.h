#ifndef CONSOLE_H
#define CONSOLE_H

#include <string>

class Console {
public:
    std::string name;
    int currentLine;
    int totalLine;
    std::string timestamp;

    Console();
    Console(std::string name, int currentLine, int totalLine);

    static std::string getCurrentTimestamp();

    void display() const;
    void display(int totalLine) const;
};

#endif // CONSOLE_H
