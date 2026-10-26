# OSConsoleCLI-CSOPESY

**Author:** Dana Louise A. Guillarte  
**Course:** CSOPESY — Introduction to Operating Systems  

---

## 📌 Project Overview

**OSConsoleCLI-CSOPESY** is a modular C++ Command-Line Interface (CLI) and Operating System Simulator shell designed for CSOPESY. It models core OS console abstractions including virtual process creation, screen session multiplexing, session re-attachment, and scheduler diagnostic routines.

### Key Capabilities
- **Terminal ASCII Banner & Command Dispatcher**: Custom styled command-line interface mimicking an OS boot console.
- **Screen Session Management**: Create (`screen -s <name>`), resume (`screen -r <name>`), and inspect (`screen -ls`) dedicated process consoles.
- **Per-Session State Tracking**: Each process session maintains isolated instruction progression counters, start timestamps, and unique identifiers.
- **Cross-Platform Compatibility**: Fully compatible with both Windows (`cls`) and POSIX/Linux (`clear`) terminal environments.
- **Scheduler Diagnostic Hooks**: Command interfaces ready for CPU scheduling routines (`scheduler-test`, `scheduler-stop`, and `report-util`).

---

## 🖥️ Frontend Architecture Status

> [!NOTE]
> **Does this project have a frontend?**  
> This project operates strictly as a **Text-based Command Line Interface (CLI) / Terminal User Interface (TUI)**. It does not utilize a web frontend (e.g., HTML/CSS/JavaScript) or a graphical desktop GUI (e.g., Qt, wxWidgets, or Java Swing). All user interactions occur through standard terminal streams (`std::cin` / `std::cout`) with terminal screen-clearing controls.

---

## 📂 Project Folder Hierarchy

The project is structured according to standard C++ software engineering conventions:

```text
OSConsoleCLI-CSOPESY/
├── bin/                        # Compiled executable binaries (.gitignore)
├── build/                      # Intermediate compilation object files (.o/.obj)
├── config/                     # Configuration and parameter files
│   └── params.txt              # Quantum, core count, scheduler type definitions
├── include/                    # C++ Header files (.h / .hpp)
│   └── Console.h               # Process console & screen session declarations
├── src/                        # C++ Implementation source files (.cpp)
│   ├── main.cpp                # Main CLI loop and command interpreter
│   └── Console.cpp             # Screen session display & timestamping logic
├── .gitignore                  # Git ignore rules for build artifacts and binaries
├── Makefile                    # Automated build script
└── README.md                   # Project documentation
```

---

## 🚀 How to Build and Run

### Prerequisites
- GCC / G++ (MinGW on Windows, or default G++ on Linux/macOS) with C++17 support.
- Make (optional, for automated builds).

### Compilation

#### Option 1: Direct g++ Command
From the project root directory:

- **Windows**:
  ```powershell
  g++ -Wall -Wextra -std=c++17 -Iinclude src/main.cpp src/Console.cpp -o bin/main.exe
  ```
- **Linux / macOS**:
  ```bash
  g++ -Wall -Wextra -std=c++17 -Iinclude src/main.cpp src/Console.cpp -o bin/main
  ```

#### Option 2: Using Makefile
```bash
make
```

### Running the Executable
- **Windows**:
  ```powershell
  .\bin\main.exe
  ```
- **Linux / macOS**:
  ```bash
  ./bin/main
  ```

---

## 💻 Available CLI Commands

| Command | Arguments | Description |
| :--- | :--- | :--- |
| `initialize` | None | Initializes system configuration and prepares scheduler worker threads. |
| `screen -s` | `<process_name>` | Creates and attaches to a new virtual process screen session. |
| `screen -r` | `<process_name>` | Re-attaches to an existing process screen session. |
| `screen -ls` | None | Lists all active process sessions with their timestamps and instruction progress. |
| `scheduler-test` | None | Initiates CPU scheduling simulation and process testing suite. |
| `scheduler-stop` | None | Halts active scheduler execution. |
| `report-util` | None | Outputs system metrics, total commands executed, and core utilization. |
| `clear` | None | Clears the terminal screen and reprints the system ASCII header. |
| `help` | None | Displays the list of available commands and their descriptions. |
| `exit` | None | Detaches from an active screen session (returns to CLI) or terminates the app. |

---

## 🛠️ Code Structure

- **[`include/Console.h`](file:///c:/Users/asus/OneDrive/Desktop/TestRepo/include/Console.h) / [`src/Console.cpp`](file:///c:/Users/asus/OneDrive/Desktop/TestRepo/src/Console.cpp)**:  
  Defines the `Console` class representing a screen session/process instance with state variables:
  - `name`: Identifier of the screen session.
  - `currentLine`: Executed instruction index.
  - `totalLine`: Total instruction count for the process.
  - `timestamp`: Formatted launch timestamp (`MM/DD/YYYY, hh:mm:ss AM/PM`).
  - `display()`: Clears the terminal and renders the session dashboard.

- **[`src/main.cpp`](file:///c:/Users/asus/OneDrive/Desktop/TestRepo/src/main.cpp)**:  
  The command-line interpreter driver managing the command dispatch loop, input sanitization, global session map (`std::map<std::string, Console>`), and active session context switches.

- **[`config/params.txt`](file:///c:/Users/asus/OneDrive/Desktop/TestRepo/config/params.txt)**:  
  Default configuration specifications defining core parameters like CPU count and scheduling algorithm.
