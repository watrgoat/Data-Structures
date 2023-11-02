#include <regex>
#include <vector>
#include <map>
#include <set>
#include <iostream>
#include <fstream>

#include "Soup.h"

using namespace std;

// step 1: web crawl.
// ingest data, store into heap (possibly custom class)

// step 2: query search
// not sure what this one is yet

// step 3: page ranking
// how to rank pages from search
// keyword density, backlinks
// Keyword Density Score = (Number of Times Keyword Appears) / (Total Content Length of this One Document * Keyword Density Across All Documents)
// keyword density score for mulitple search terms = (kwdensity1 + kwdensity2 + ...)
// backlinks score = ( 1.0 / (1 + doc_1->outgoingLinks) + 1.0 / (1 + doc_2->outgoingLinks) + ... + 1.0 / (1 + doc_N->outgoingLinks) );

// page score = (0.5 * keywords density score + 0.5 * backlinks score);


// notes to grader:
// my initial thoughts go to the inverse word search, i believe that it would be more
// memory efficient to map each url (document) into an integer value or some defined
// set of values and then assign that as the values in the inverted index map, this
// would be necessary in a real web scraper as url lengths are theoretically infinite
// and should be handled with care, not wanting to store that many times over.

// big overview:
// scrape all of the input files


// function to parse an HTML file and extract links to local files
vector<string> extractLinksFromHTML(const string& fileContent) {
    vector<string> links;
    // regular expression to match href attributes in anchor tags
    regex linkRegex("<a\\s+[^>]*href\\s*=\\s*['\"]([^'\"]+)['\"][^>]*>");
    smatch match;

    // search for links in the HTML content
    string::const_iterator start = fileContent.cbegin();
    while (regex_search(start, fileContent.cend(), match, linkRegex)) {
        if (match.size() > 1) {
            links.push_back(match[1].str());
        }
        start = match.suffix().first;
    }

    return links;
}

// expand this function to get all the information needed from each url connected to the first url
// create new class for each url
// recursive url function
void webCrawl(string url, string currentDir, map<string, Soup> &pages, set<string> &visited) {
    // check if url has been visited
    if (visited.find(url) != visited.end()) {
        return;
    }

    // open file
    std::ifstream fileStream(filePath);
    if (fileStream.is_open()) {
        std::string fileContent((std::istreambuf_iterator<char>(fileStream)), std::istreambuf_iterator<char>());
        // suppose filePath is the string "html_files/subdir1/file3.html", then at this point, the string fileContent will be the full content of this file file3.html.
        // do something with fileContent
    }

    // read file into string
}

int main(int argc, char* argv[]) {
    // check command line arguments len 4-6
    if (argc < 4 || argc > 6) {
        cout << "Usage: " << argv[0] << " <input file> <output file> <query/phrase search>" << endl;
        return 1;
    }

    // recursively crawl the web
    // create a vector of Soup objects
    vector<Soup> pages;
    // create a set of visited urls
    set<string> visited;

    webCrawl(argv[1], pages, visited);



}