#include <iostream>
#include <string>
#include <cstdlib>
#include <map>
#include <ctime>
#include <sstream>
#include <iomanip>
#if __has_include("../include/Console.h")
#include "../include/Console.h"
#else
#include "Console.h"
#endif

using namespace std;

map<string, Console> sessions;
bool in_session = false;
int total_line = 0;

string current_session_name = "";

string trim(const string& str) {
    size_t first = str.find_first_not_of(" \t\r\n");
    if (first == string::npos) return "";
    size_t last = str.find_last_not_of(" \t\r\n");
    return str.substr(first, (last - first + 1));
}

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
    #else
        system("clear");
    #endif
    printHeader();
}

void processCommand(const string& raw_command) {
    string command = trim(raw_command);
    if (command.empty()) {
        return;
    }

    if (command == "initialize") {
        cout << "Initialize command recognized. System initialized successfully." << endl;
    }
    else if (command == "screen -ls") {
        if (sessions.empty()) {
            cout << "No active screen sessions." << endl;
        } else {
            cout << "Active sessions (" << sessions.size() << "):" << endl;
            for (const auto& pair : sessions) {
                cout << "  - " << pair.first << " (Started at: " << pair.second.timestamp 
                     << ", Instructions: " << pair.second.currentLine << "/" << pair.second.totalLine << ")" << endl;
            }
        }
    }
    else if (command.rfind("screen", 0) == 0) {
        if (in_session) {
            cout << "Already attached to session '" << current_session_name << "'. Type 'exit' to detach first." << endl;
            return;
        }

        size_t s_pos = command.find("-s ");
        size_t r_pos = command.find("-r ");
        
        if (s_pos != std::string::npos) {
            std::string name = trim(command.substr(s_pos + 3));
            if (name.empty()) {
                std::cout << "Please provide a valid session name after '-s'." << std::endl;
            } else {
                if (sessions.find(name) != sessions.end()) {
                    std::cout << "Session '" << name << "' already exists. Use 'screen -r " << name << "' to resume." << std::endl;
                } else {
                    int processInstructions = (total_line > 0) ? total_line : 100;
                    Console console(name, 0, processInstructions);
                    sessions[name] = console;
                    in_session = true;
                    current_session_name = name;
                    console.display();
                    std::cout << "\nAttached to session '" << name << "'. Type 'exit' to return to main CLI." << std::endl;
                }
            }
        }
        else if (r_pos != std::string::npos) {
            std::string name = trim(command.substr(r_pos + 3));
            if (name.empty()) {
                std::cout << "Please provide a valid session name after '-r'." << std::endl;
            } else {
                if (sessions.find(name) != sessions.end()) {
                    in_session = true;
                    current_session_name = name;
                    sessions[name].display();
                    std::cout << "\nResumed session '" << name << "'. Type 'exit' to return to main CLI." << std::endl;
                } else {
                    std::cout << "Session '" << name << "' does not exist. Use 'screen -ls' to list active sessions." << std::endl;
                }
            }
        }
        else {
            std::cout << "Invalid screen command. Usage:\n"
                      << "  screen -s <name>  : Create and attach to a new session\n"
                      << "  screen -r <name>  : Resume an existing session\n"
                      << "  screen -ls        : List all active sessions" << std::endl;
        }
    }
    else if (command == "scheduler-test") {
        cout << "Scheduler-test command recognized. Starting scheduler test suite..." << endl;
    }
    else if (command == "scheduler-stop") {
        cout << "Scheduler-stop command recognized. Scheduler stopped." << endl;
    }
    else if (command == "report-util") {
        cout << "Report-util command recognized. Generating CPU and memory utilization report..." << endl;
        cout << "Active sessions: " << sessions.size() << endl;
        cout << "Total CLI commands executed: " << total_line << endl;
    }
    else if (command == "clear") {
        clearScreen();
    }
    else if (command == "help") {
        cout << "\nAvailable commands:" << endl;
        cout << "  initialize        : Initialize the system configuration" << endl;
        cout << "  screen -s <name>  : Create and attach to a new process screen session" << endl;
        cout << "  screen -r <name>  : Resume / re-attach to an existing screen session" << endl;
        cout << "  screen -ls        : List all active screen sessions" << endl;
        cout << "  scheduler-test    : Run CPU scheduler testing suite" << endl;
        cout << "  scheduler-stop    : Stop running CPU scheduler" << endl;
        cout << "  report-util       : Display system and resource utilization report" << endl;
        cout << "  clear             : Clear the terminal screen and display header" << endl;
        cout << "  exit              : Detach from session (if inside screen) or exit application" << endl;
        cout << "  help              : Display this help message" << endl;
    }
    else if (command == "exit" && in_session) {
        clearScreen();
        in_session = false;
        cout << "Detached from session '" << current_session_name << "'." << endl;
        current_session_name = "";
    }
    else if (command != "exit") {
        cout << "Unknown command '" << command << "'. Type 'help' for available commands." << endl;
    }
}

int main() {
    string command;
    
    // Print initial header
    clearScreen();
    
    // Main command loop
    while (true) {
        if (in_session) {
            cout << "\n[" << current_session_name << "] > ";
        } else {
            cout << "\n> ";
        }
        
        if (!getline(cin, command)) {
            break;
        }
        
        string trimmed = trim(command);
        if (trimmed.empty()) {
            continue;
        }
        
        if (trimmed == "exit" && !in_session) {
            cout << "Exit command recognized. Closing the application..." << endl;
            break;
        }
        
        processCommand(trimmed);
        total_line++;
    }
    
    return 0;
}
