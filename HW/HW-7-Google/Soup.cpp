#include "Soup.h"

// def constructor
Soup::Soup() {
    string *title_ = new string();
    string *content_ = new string();
    vector<string> *outlinks_ = new vector<string>();
    int count_ = 0;
}

// constructor
Soup::Soup(string title, string content, vector<string> outlinks, vector<string> inlinks) {
    string *title_ = new string(title);
    string *content_ = new string(content);
    vector<string> *outlinks_ = new vector<string>(outlinks);
    int count_ = 0;
}

// destructor
Soup::~Soup() {
    delete title_;
    delete content_;
    delete outlinks_;
}

// operator overloads
bool operator==(const Soup& other) {
    // check title
    if (title_ != other.getTitle()) {
        return false;
    }
    // check body
    if (content_ != other.getContent()) {
        return false;
    }
    // check outlinks
    if (outlinks_ != other.getOutlinks()) {
        return false;
    }
    // check count
    if (count_ != other.getCount()) {
        return false;
    }
    return true;
}

bool operator!=(const Soup& other) {
    return !(*this == other);
}

bool operator<(const Soup& other) {
    // check title
    if (title_ < other.getTitle()) {
        return true;
    }
    // check body
    if (content_ < other.getContent()) {
        return true;
    }
    // check outlinks
    if (outlinks_ < other.getOutlinks()) {
        return true;
    }
    // check count
    if (count_ < other.getCount()) {
        return true;
    }
    return false;
}

bool operator>(const Soup& other) {
    return !(*this < other);
}

// getters
string getTitle() {
    return *title_;
}

string getContent() {
    return *content_;
}

vector<string> getOutlinks() {
    return *outlinks_;
}

int getCount() {
    return count_;
}

// edit links
void addOutlink(string outlink) {
    outlinks_->push_back(outlink);
}

void removeOutlink(string outlink) {
    for (int i = 0; i < outlinks_->size(); i++) {
        if (outlinks_->at(i) == outlink) {
            outlinks_->erase(outlinks_->begin() + i);
        }
    }
}