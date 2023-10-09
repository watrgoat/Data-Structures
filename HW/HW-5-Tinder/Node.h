#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <fstream>
#include <string>

class Node {
public:
    std::string data;
    Node* next;
    Node* prev;
};

std::ostream& operator<<(std::ostream& os, const Node& node) {
    os << node.data;
    return os;
}

#endif // NODE_H