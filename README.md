# Multithreaded C++ Web Server

A simple multithreaded web server written in C++ that handles HTTP GET requests and serves static files.

## Features
- Thread pool for concurrent connections
- Serves files from `www/` directory
- Basic HTTP response handling

## Build Instructions
```bash
mkdir build
cd build
cmake ..
make
./server
