cmake_minimum_required(VERSION 3.15)
project(TDD_CLION C)

set(CMAKE_C_STANDARD 99)

add_executable(
        TDD_CLION main.c
        src/player.h src/player.c
        src/gpio.h src/gpio.c
)
