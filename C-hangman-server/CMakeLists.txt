cmake_minimum_required(VERSION 3.25)
project(C_hangman_server C)

set(CMAKE_C_STANDARD 11)

add_executable(C_hangman_server hangserver_iter.c hangserver_iter.c)
