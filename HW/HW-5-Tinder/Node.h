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

std::ostream& operator<<(std::ostream& out, const Node& node) {
    out << node.data;
    return out;
}

#endif // NODE_H