#include "../include/net_func.h"
#include <iostream>
#include <zmq.hpp>
#include <sstream>
#include <vector>
#include <unordered_set>
#include <unistd.h>

std::unordered_set<int> active_nodes;

int main() {
    zmq::context_t context(1);
    zmq::socket_t socket(context, ZMQ_REQ);
    std::string command;

    std::cout << "Client started. Enter commands (create, ping, exec, remove, exit):" << std::endl;

    while (true) {
        std::cout << "> ";
        std::getline(std::cin, command);
        std::istringstream iss(command);
        std::string cmd;
        iss >> cmd;

        if (cmd == "create") {
            int id;
            iss >> id;
            if (active_nodes.find(id) != active_nodes.end()) {
                std::cout << "Error: Worker " << id << " already exists" << std::endl;
                continue;
            }

            std::string worker_command = "./worker " + std::to_string(id) + " -1 &";
            int status = system(worker_command.c_str());
            if (status == -1) {
                std::cout << "Error: Failed to start worker" << std::endl;
                continue;
            }

            sleep(1);
            my_net::connect(&socket, 4040 + id);
            my_net::send_message(&socket, "ping " + std::to_string(id));
            std::string response = my_net::reseave(&socket);

            if (response == "Ok: 1") {
                active_nodes.insert(id);
                std::cout << "Worker " << id << " started successfully on port " << (4040 + id) << std::endl;
            } else {
                std::cout << "Error: Worker did not respond" << std::endl;
            }
        } 
        else if (cmd == "ping") {
            int id;
            iss >> id;
            if (active_nodes.find(id) == active_nodes.end()) {
                std::cout << "Error: Worker " << id << " not found" << std::endl;
                continue;
            }

            my_net::send_message(&socket, "ping " + std::to_string(id));
            std::string response = my_net::reseave(&socket);
            std::cout << response << std::endl;
        } 
        else if (cmd == "exec") {
            int id, n;
            iss >> id >> n;
            if (active_nodes.find(id) == active_nodes.end()) {
                std::cout << "Error: Worker " << id << " not found" << std::endl;
                continue;
            }

            std::vector<int> numbers(n);
            for (int i = 0; i < n; ++i) {
                iss >> numbers[i];
            }

            std::ostringstream oss;
            oss << "exec " << n;
            for (int num : numbers) {
                oss << " " << num;
            }

            my_net::send_message(&socket, oss.str());
            std::string response = my_net::reseave(&socket);
            std::cout << response << std::endl;
        } 
        else if (cmd == "remove") {
            int id;
            iss >> id;
            if (active_nodes.find(id) == active_nodes.end()) {
                std::cout << "Error: Worker " << id << " not found" << std::endl;
                continue;
            }

            my_net::send_message(&socket, "remove " + std::to_string(id));
            std::string response = my_net::reseave(&socket);
            std::cout << response << std::endl;

            std::string kill_command = "pkill -SIGTERM -f \"./worker " + std::to_string(id) + " -1\"";
            system(kill_command.c_str());
            usleep(500000); 
            std::string force_kill_command = "pkill -9 -f \"./worker " + std::to_string(id) + " -1\"";
            system(force_kill_command.c_str());

            active_nodes.erase(id);
        } 
        else if (cmd == "exit") {
            std::cout << "Exiting... Removing all workers." << std::endl;

            for (int id : active_nodes) {
                std::cout << "Removing worker " << id << std::endl;
                my_net::send_message(&socket, "remove " + std::to_string(id));
                std::string response = my_net::reseave(&socket);
                std::cout << response << std::endl;

                std::string kill_command = "pkill -SIGTERM -f \"./worker " + std::to_string(id) + " -1\"";
                system(kill_command.c_str());
                usleep(500000);
                std::string force_kill_command = "pkill -9 -f \"./worker " + std::to_string(id) + " -1\"";
                system(force_kill_command.c_str());
            }

            system("pkill -SIGTERM -f ./worker");
            usleep(500000);
            system("pkill -9 -f ./worker");

            std::cout << "All workers removed. Exiting client." << std::endl;
            active_nodes.clear();
            break;
        } 
        else {
            std::cout << "Unknown command" << std::endl;
        }
    }

    return 0;
}
