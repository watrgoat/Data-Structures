#include "Soup.h"

// def constructor
Soup::Soup() {
    string *title_ = new string();
    string *body_ = new string();
    vector<string> *outlinks_ = new vector<string>();
    vector<string> *inlinks_ = new vector<string>();
}

// constructor
Soup::Soup(string title, string body, vector<string> outlinks, vector<string> inlinks) {
    string *title_ = new string(title);
    string *body_ = new string(body);
    vector<string> *outlinks_ = new vector<string>(outlinks);
    vector<string> *inlinks_ = new vector<string>(inlinks);
}

// destructor
Soup::~Soup() {
    delete title_;
    delete body_;
    delete outlinks_;
    delete inlinks_;
}
