cmake_minimum_required(VERSION 3.0)
project(Linux-Emulator)

set(SOURCES 
    main.cpp
    emulator.cpp
    file.cpp
    folder.cpp
    result.cpp
    scenario.cpp

    Cube-Encription/src/encryption.cpp
    Commands/mkdir.cpp
    Commands/cd.cpp
    Commands/pwd.cpp
    Commands/rm.cpp
    Commands/adduser.cpp
    Commands/deluser.cpp
    Commands/su.cpp
)

add_executable(Linux-Emulator ${SOURCES})