#pragma once
#include <string>

class WebServer {
public:
    WebServer(int port, const std::string& root_dir, int thread_count);
    void start();

private:
    int port_;
    std::string root_dir_;
    int thread_count_;
};
