#pragma once
#include <iostream>
#include <unordered_map>
#include <vector>

class Node {
private:
    int id;
    int parent_id;
    std::unordered_map<int, Node*> children;

public:
    explicit Node(int _id, int _parent_id = -1) : id(_id), parent_id(_parent_id) {}

    bool Create_child(int child_id) {
        if (children.find(child_id) != children.end()) {
            return false; 
        }
        children[child_id] = new Node(child_id, id);
        return true;
    }

    bool Remove_child(int child_id) {
        if (children.find(child_id) == children.end()) {
            return false;
        }
        delete children[child_id];
        children.erase(child_id);
        return true;
    }

    bool Ping_child(int child_id) {
        return children.find(child_id) != children.end();
    }

    int Exec_sum(const std::vector<int>& numbers) {
        int sum = 0;
        for (int num : numbers) {
            sum += num;
        }
        return sum;
    }

    std::string Send(std::string msg, int _id) {
        return "Ok: Simulated response for " + msg;
    }

    ~Node() {
        for (auto& pair : children) {
            delete pair.second;
        }
    }
};
