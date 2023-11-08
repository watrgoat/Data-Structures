#ifndef SOUP_H
#define SOUP_H

#include <string>
#include <vector>
#include <set>
#include <sstream>
#include <iostream>
#include <regex>

using namespace std;

/*
Soup:

Class for storing HTML data from a web page.

    - title: title of the web page
    - body: body of the web page
    - outlinks: list of URLs that the web page links to
*/

class Soup {
public:
    // constructors
    Soup();
    Soup(const string& content);
    Soup(const Soup& other);
    Soup(Soup&& other) noexcept;

    // operator overloads
    Soup& operator=(const Soup& other);
    bool operator==(const Soup& other) const;
    bool operator!=(const Soup& other) const;
    bool operator<(const Soup& other) const;
    bool operator>(const Soup& other) const;

    // getters
    string getTitle() const;
    string getContent() const;
    vector<string> getOutlinks() const;
    set<string> getBody() const;
    int getCount(string word) const;
    string getDescription() const;

    // edit links
    void addOutlink(const string& outlink);
    void removeOutlink(const string& outlink);

private:
    string title_;
    string content_;
    vector<string> outlinks_;
    set<string> body_;
    string description_;
};

// overload << operator
ostream& operator<<(ostream& os, const Soup& soup);

#endif // SOUP_H