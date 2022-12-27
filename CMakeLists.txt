cmake_minimum_required(VERSION 3.24)
project(SOproject C)

set(CMAKE_C_STANDARD 11)

add_executable(SOproject server/main.c client/client.c server/server.h server/functions.c)
