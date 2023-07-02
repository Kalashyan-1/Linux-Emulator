# Linux Emulator

Linux Emulator is an educational program that emulates Linux commands and quizzes users on their knowledge of these commands. It is providing a hands-on learning experience for users to practice using various Linux commands.

## Features

- Emulates common Linux commands such as `cd`, `mkdir`, `adduser`, `deluser`, and more.
- Interactive quiz format that prompts users with questions about each command.
- Checks user answers and provides immediate feedback on whether the answer is correct or incorrect.
- Automatically performs the necessary operation if the user's answer is incorrect and proceeds to the next question.
- Maintains a list of questions with correct answers for review at the end of execution.
- Calculates the percentage of correct answers to assess the user's performance.

## Usage

To use the Linux Emulator program, follow these steps:

1. Clone the repository or download the program files.
    - `https://github.com/Kalashyan-1/Linux-Emulator.git`
2. Open a terminal and navigate to the program directory.
3. Create a build directory: 
    -  `mkdir build`
    -  `cd build`
4. Generate the build files using CMake:
    -  `cmake ..`
5. Build the program using the appropriate build system. For example, on Unix-like systems, use make:
    -  `make `
6. Run the program by executing the executable:
    `./LinuxEmulator`

7. The program will present questions about various Linux commands one by one.
8. Enter your answer for each question and press Enter.
9. The program will provide immediate feedback on whether your answer is correct or incorrect.
10. At the end of the execution, the program will display a list of questions with the correct answers.
11. It will also calculate and display the percentage of correct answers as a measure of your performance.

## Dependencies

The Linux Emulator program has the following dependencies:

1. C++ compiler supporting C++11 or later
2. Standard Library (STL)
3. CMake (minimum version 3.0)
Please make sure that you have CMake installed on your system before proceeding with the build and compilation of the program.

If CMake is not installed, you can install it by following the instructions for your specific operating system:

- Ubuntu/Debian: `sudo apt-get install cmake`
- Fedora: `sudo dnf install cmake`
- macOS (Homebrew): `brew install cmake`
- Windows:
You can download the CMake installer from the official website: `https://cmake.org/download/`

Please ensure that you have the necessary dependencies installed before attempting to build and run the Linux Emulator program.

## Screenshots

![Screenshot 1](https://github.com/Kalashyan-1/Linux-Emulator/assets/114615404/8fc69730-e66b-432c-9270-e66a0205bd1e)

![Screenshot 2](https://github.com/Kalashyan-1/Linux-Emulator/assets/114615404/6fcebdd6-6092-43e8-bb90-c2f29f8e3130)


## Contributing

Contributions to the Linux Emulator project are welcome! If you have any ideas, suggestions, or bug reports, please feel free to open an issue or submit a pull request.


## Acknowledgements

The Linux Emulator program is inspired by the Linux command-line interface and aims to provide a learning tool for beginners.
The program utilizes the knowledge and resources available in the Linux community.
