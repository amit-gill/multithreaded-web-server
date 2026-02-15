cmake_minimum_required(VERSION 3.10)
project(MultithreadedWebServer)

set(CMAKE_CXX_STANDARD 17)

add_executable(server
    src/main.cpp
    src/server.cpp
)

target_include_directories(server PRIVATE src)
