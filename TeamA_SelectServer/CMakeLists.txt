cmake_minimum_required(VERSION 3.26)
project(TeamA_SelectServer C)

set(CMAKE_C_STANDARD 11)

add_executable(TeamA_SelectServer hangman.h SelectServer.c TCPConnectionSetup.h)
