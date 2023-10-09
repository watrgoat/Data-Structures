#include <iostream>
#include <fstream>
#include <string>
#include "Node.h"

int main(int argc, char* argv[]) {

    Node* head = new Node();
    head->data = "Hello";
    Node* tail = new Node();
    tail->data = "World";
    head->next = tail;
    head->prev = nullptr;
    tail->next = nullptr;
    tail->prev = head;

    std::cout << head << ", " << head->next << std::endl;

    return 0;
}