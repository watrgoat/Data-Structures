#include <regex>
#include <vector>
#include <map>
#include <set>
#include <iostream>
#include <fstream>

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
// write a map for each word and their assosiated url
// 


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
void retrieveLinks(string url, map<string, vector<string>> &backlinks, set<string> &visited) {
    // open file
    ifstream file(url);
    string line;
    string content;
    // read file into string
    while (getline(file, line)) {
        content += line;
    }
    // extract links from html
    vector<string> links = extractLinksFromHTML(content);
    // add links to map
    backlinks[url] = links;
    // recursively call url on each link
    for (string link : links) {
        // only if not already in visited set
        if (visited.find(link) == visited.end()) {
            visited.insert(link);
            retrieveLinks(link, backlinks, visited);
        }
    }
}

int main(int argc, char* argv[]) {
    // check command line arguments len 4-6
    if (argc < 4 || argc > 6) {
        cout << "Usage: " << argv[0] << " <input file> <output file> <query 1-3>" << endl;
        return 1;
    }

    // recursively give function a "url" and it adds to map of backlinks
    map<string, vector<string>> backlinks;
    set<string> visited;



}