#include <string>
#include <vector>

#include "Soup.h"

// def constructor
Soup::Soup() {
    // stores in heap
    string title_ = new string();
    string body_ = new string();
    vector<string> outlinks_ = new vector<string>();
    vector<string> inlinks_ = new vector<string>();
}

Soup::Soup(string title, string body, vector<string> outlinks, vector<string> inlinks) {
    title_ = title;
    body_ = body;
    outlinks_ = outlinks;
    inlinks_ = inlinks;
}

Soup::~Soup() {
    // nothing to do here
}
