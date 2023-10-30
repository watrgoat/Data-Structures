#ifndef SOUP_H
#define SOUP_H

#include <string>
#include <vector>

// SHOULD I KNOW MY OWN URL???

/*
Soup:

Class for storing HTML data from a web page.

    - 
*/

class Soup {
private:
    string title_;
    string body_;
    vector<string> outlinks_;
    vector<string> inlinks_;

};

#endif