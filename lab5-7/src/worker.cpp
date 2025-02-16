#include "../include/node.h"
#include "../include/net_func.h"
#include <iostream>
#include <sstream>
#include <vector>
#include <zmq.hpp>
#include <csignal>
#include <unistd.h>

int my_id = 0;
bool running = true;

void handle_signal(int signum) {
    std::cout << "Worker " << my_id << " shutting down..." << std::endl;
    running = false;
}

int main(int argc, char **argv) {
    if (argc != 3) {
        return -1;
    }

    my_id = atoi(argv[1]);
    Node me(my_id, atoi(argv[2]));

    zmq::context_t context(1);
    zmq::socket_t socket(context, ZMQ_REP);

    int port = 4040 + my_id;
    std::string address = "tcp://127.0.0.1:" + std::to_string(port);

    try {
        socket.bind(address);
    } catch (const zmq::error_t& e) {
        std::cerr << "Error: Failed to bind socket on port " << port << " - " << e.what() << std::endl;
        return -1;
    }

    std::cout << "Worker " << my_id << " started on port " << port << std::endl;

    signal(SIGTERM, handle_signal);
    signal(SIGINT, handle_signal);

    while (running) {
        zmq::message_t request;
        try {
            socket.recv(request, zmq::recv_flags::none);
        } catch (const zmq::error_t& e) {
            if (running) {
                std::cerr << "Receive error: " << e.what() << std::endl;
            }
            break;
        }

        std::string message(static_cast<char*>(request.data()), request.size());
        std::istringstream iss(message);
        std::string cmd;
        iss >> cmd;

        if (cmd == "ping") {
            my_net::send_message(&socket, "Ok: 1");
        } 
        else if (cmd == "exec") {
            int n;
            iss >> n;
            std::vector<int> numbers(n);
            for (int i = 0; i < n; ++i) {
                iss >> numbers[i];
            }

            if (numbers.size() != static_cast<size_t>(n)) {
                my_net::send_message(&socket, "Error: Invalid number of arguments");
                continue;
            }

            int result = me.Exec_sum(numbers);
            my_net::send_message(&socket, "Ok: " + std::to_string(result));
        } 
        else if (cmd == "remove") {
            my_net::send_message(&socket, "Ok");
            running = false;
        } 
        else {
            my_net::send_message(&socket, "Error: Unknown command");
        }
    }

    std::cout << "Worker " << my_id << " exited successfully." << std::endl;
    return 0;
}
