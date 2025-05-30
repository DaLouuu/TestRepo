#include <iostream>
#include <string>
#include <cstdlib>
#include <map>
#include <ctime>
#include <sstream>
#include <iomanip>
#include "Console.h"

using namespace std;

map<string, Console> sessions;
bool in_session = false;
int total_line = 0;

void printHeader() {
    cout << " ,-----. ,---.   ,-----. ,------. ,------. ,---.,--.   ,--.  " << endl;
    cout << "'  .--./'   .-' '  .-.  '|  .--. '|  .---''   .-'\\  `.'  /  " << endl;
    cout << "|  |    `.  `-. |  | |  ||  '--' ||  `--, `.  `-. '.    /   " << endl;
    cout << "'  '--'\\.-'    |'  '-'  '|  | --' |  `---..-'    |  |  |    " << endl;
    cout << " `-----'`-----'  `-----' `--'     `------'`-----'   `--'     " << endl;
    cout << "\nCommand Line Interface" << endl;
    cout << "Type 'help' to see available commands" << endl;
}

void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #endif
    printHeader();
}

void processCommand(const string& command) {
    if (command == "initialize") {
        cout << "Initialize command recognized. Doing something." << endl;
    }
    else if (command.find("screen") == 0) {
    size_t s_pos = command.find("-s ");
    size_t r_pos = command.find("-r ");
        
        if (s_pos != std::string::npos) {
            std::string name = command.substr(s_pos + 3);
            if (name.empty()) {
                std::cout << "Please provide a session name after '-s'." << std::endl;
            } else {
                 if (sessions.find(name) != sessions.end()) {
                    std::cout << "Session '" << name << "' already exists." << std::endl;
                } else {
                    Console console(name, total_line, total_line);
                    sessions[name] = console;
                    std::cout << "Session '" << name << "' created." << std::endl;
                    in_session = true;
                    console.display(total_line);
                }
            }
        }
        else if (r_pos != std::string::npos) {
            std::string name = command.substr(r_pos + 3);
            if (name.empty()) {
                std::cout << "Please provide a session name after '-r'." << std::endl;
            } else {
                 if (sessions.find(name) != sessions.end()) {
                    std::cout << "Session '" << name << "' resumed." << std::endl;
                    in_session = true;
                    sessions[name].display(total_line);
                } else {
                    std::cout << "Session '" << name << "' does not exist." << std::endl;
                }
            }
        }
        else {
            std::cout << "Please provide a proper 'screen' command with '-s <name>' to create or '-r <name>' to resume a session." << std::endl;
        }
    }
    else if (command == "scheduler-test") {
        cout << "Scheduler-test command recognized. Doing something." << endl;
    }
    else if (command == "scheduler-stop") {
        cout << "Scheduler-stop command recognized. Doing something." << endl;
    }
    else if (command == "report-util") {
        cout << "Report-util command recognized. Doing something." << endl;
    }
    else if (command == "clear") {
        clearScreen();
    }
    else if (command == "help") {
        cout << "\nAvailable commands:" << endl;
        cout << "- initialize: Initialize the system" << endl;
        cout << "- screen: Display screen information" << endl;
        cout << "- scheduler-test: Test the scheduler" << endl;
        cout << "- scheduler-stop: Stop the scheduler" << endl;
        cout << "- report-util: Generate utility report" << endl;
        cout << "- clear: Clear the screen" << endl;
        cout << "- exit: Exit the program" << endl;
        cout << "- help: Display this help message" << endl;
    }
    else if (command == "exit" && in_session == true){
        system("cls");
        printHeader();
        in_session = false;
    }
    else if (command != "exit") {
        cout << "Unknown command. Type 'help' for available commands." << endl;
    }
}

int main() {
    string command;
    
    // Print initial header
    clearScreen();
    
    // Main command loop
    while (true) {
        cout << "\n> ";
        getline(cin, command);
        
        if (command == "exit" && in_session == false) {
            cout << "Exit command recognized. Closing the application..." << endl;
            break;
        }
        
        processCommand(command);
        total_line++;
    }
    
    return 0;
}