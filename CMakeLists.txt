cmake_minimum_required(VERSION 3.23)
project(wazuh_monty_hall C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -pthread")
add_executable(wazuh_monty_hall main.c randomizer.c randomizer.h monty_hall.c monty_hall.h)
