#include "server.hpp"
#include "thread_pool.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <thread>
#include <vector>
#include <netinet/in.h>
#include <unistd.h>

WebServer::WebServer(int port, const std::string& root_dir, int thread_count)
    : port_(port), root_dir_(root_dir), thread_count_(thread_count) {}

void handle_client(int client_socket, const std::string& root_dir) {
    char buffer[1024] = {0};
    read(client_socket, buffer, 1024);

    std::string request(buffer);
    std::istringstream request_stream(request);
    std::string method, path;
    request_stream >> method >> path;

    if (method != "GET") {
        close(client_socket);
        return;
    }

    std::string file_path = root_dir + (path == "/" ? "/index.html" : path);
    std::ifstream file(file_path);
    std::string response;

    if (file) {
        std::ostringstream ss;
        ss << file.rdbuf();
        response = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n" + ss.str();
    } else {
        response = "HTTP/1.1 404 Not Found\r\nContent-Type: text/html\r\n\r\n<h1>404 Not Found</h1>";
    }

    send(client_socket, response.c_str(), response.size(), 0);
    close(client_socket);
}

void WebServer::start() {
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in address = {AF_INET, htons(port_), INADDR_ANY};
    bind(server_fd, (struct sockaddr*)&address, sizeof(address));
    listen(server_fd, 10);

    ThreadPool pool(thread_count_);

    std::cout << "Server started on port " << port_ << std::endl;

    while (true) {
        int client_socket = accept(server_fd, nullptr, nullptr);
        pool.enqueue(client_socket, this {
            handle_client(client_socket, root_dir_);
        });
    }
}
