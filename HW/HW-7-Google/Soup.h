#ifndef SOUP_H
#define SOUP_H

#include <string>
#include <vector>

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
private:
    string title_;
    string body_;
    vector<string> outlinks_;
    vector<string> inlinks_;
public:
    // constructors
    Soup();
    Soup(string title, string body, vector<string> outlinks, vector<string> inlinks);

    // destructor
    ~Soup();

    // getters
    string getTitle();
    string getBody();
    vector<string> getOutlinks();
    vector<string> getInlinks();

    // setters
    void setTitle(string title);
    void setBody(string body);
    // possibly unnessesary
    void setOutlinks(vector<string> outlinks);
    void setInlinks(vector<string> inlinks);

    // edit links
    void addOutlink(string outlink);
    void addInlink(string inlink);
    void removeOutlink(string outlink);
    void removeInlink(string inlink);

    // clear
    void clear();
};

// overload << operator
ostream& operator<<(ostream& os, const Soup& soup);

#endif