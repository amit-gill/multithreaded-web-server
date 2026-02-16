#include "server.hpp"

int main() {
    std::string base_dir = "../www";
    WebServer server(8080, "../www", 1); // Port, root directory, thread count
    server.start();
    return 0;
}
