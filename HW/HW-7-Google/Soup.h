#ifndef SOUP_H
#define SOUP_H

#include <string>
#include <vector>

using namespace std;

// SHOULD I KNOW MY OWN URL???

/*
Soup:

Class for storing HTML data from a web page.

    - title: title of the web page
    - body: body of the web page
    - outlinks: list of URLs that the web page links to
    - inlinks: list of URLs that link to the web page
*/

class Soup {
public:
    // constructors
    Soup();
    Soup(string title, string content, vector<string> outlinks, int count);

    // destructor
    ~Soup();

    // operator overloads
    bool operator==(const Soup& other) const;
    bool operator!=(const Soup& other) const;
    bool operator<(const Soup& other) const;
    bool operator>(const Soup& other) const;

    // getters
    string getTitle() const;
    string getContent() const;
    vector<string> getOutlinks() const;
    int getCount() const;

    // edit links
    void addOutlink(string outlink);
    void removeOutlink(string outlink);

private:
    string *title_;
    string *content_;
    vector<string> *outlinks_;
    int count_;
};

// overload << operator
ostream& operator<<(ostream& os, const Soup& soup);
