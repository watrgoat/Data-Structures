#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <algorithm>
#include <iterator>

#include "Soup.h"

using namespace std;

// todo :
// dont use set use pair int, int for body in Soup to store start and end loc for less memory usage



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

// adjusts paths to find absolute path
string resolvePath(const string& basePath, const string& relativePath) {
    vector<string> baseParts;
    vector<string> relativeParts;
    istringstream baseStream(basePath);
    istringstream relativeStream(relativePath);
    string temp;

    // split base path into parts
    while (getline(baseStream, temp, '/')) {
        if (temp != "." && !temp.empty()) {
            baseParts.push_back(temp);
        }
    }

    // split relative path into parts
    while (getline(relativeStream, temp, '/')) {
        if (temp == "..") {
            if (!baseParts.empty()) {
                baseParts.pop_back();
            }
        } else if (temp != "." && !temp.empty()) {
            relativeParts.push_back(temp);
        }
    }

    // combine the parts into a single path
    ostringstream resolvedPath;
    for (const auto& part : baseParts) {
        resolvedPath << part << "/";
    }
    for (const auto& part : relativeParts) {
        resolvedPath << part << "/";
    }

    string resolved = resolvedPath.str();
    resolved.pop_back(); // remove slash at end

    return resolved;
}

Soup readFileIntoSoup(const string &path) {
    ifstream fileStream(path);
    if (!fileStream.is_open()) {
        cerr << "Could not open the file - '" << path << "'" << endl;
        exit(1);
    }
    string fileContent((istreambuf_iterator<char>(fileStream)), istreambuf_iterator<char>());
    Soup soup(fileContent);
    return soup;
}

void webCrawl(string basePath, string url, map<string, Soup> &pages) {
    // Resolve the relative path
    string resolvedPath = resolvePath(basePath, url);
    // check if path isnt in pages
    if (pages.find(resolvedPath) == pages.end()) {
        pages[resolvedPath] = (readFileIntoSoup(resolvedPath));

        for (string relativePath : pages[resolvedPath].getOutlinks()) {
            // Construct new base path by removing the file name from the resolved path
            string newBasePath = resolvedPath.substr(0, resolvedPath.find_last_of('/'));
            webCrawl(newBasePath, relativePath, pages);
        }
    }
}

// phrase vs regular search
// regular search what do i need
// does any of the query words appear in body
// if so .find count each word in all found documents

map<string, vector<string> > invertLinks(const map<string, Soup>& pages) {
    map<string, vector<string> > backlinks_map;
    
    for (const pair<string, Soup> pair : pages) {
        const string& page = pair.first;
        const vector<string>& outgoing_links = pair.second.getOutlinks();
        
        for (const string& linked_page : outgoing_links) {
            backlinks_map[linked_page].push_back(page);
        }
    }
    
    return backlinks_map;
}

bool containsWord(const string& word, const set<string>& body) {
    return body.find(word) != body.end();
}

bool containsAllWords(const vector<string>& query, const set<string>& body) {
    for (const auto& word : query) {
        if (body.find(word) == body.end()) {
            return false;
        }
    }
    return true;
}

map<string, double> calculateBacklinksScore(const map<string, vector<string> >& backlinks_map, const map<string, Soup>& pages) {
    map<string, double> backlinks_scores;
    
    // Initialize backlink scores to zero for all pages
    for (const pair<string, Soup> pair : pages) {
        backlinks_scores[pair.first] = 0.0;
    }

    // Calculate backlink scores
    for (const auto& pair : backlinks_map) {
        const string& page = pair.first;
        const vector<string>& incoming_links = pair.second;
        
        for (const string& incoming_link : incoming_links) {
            unsigned int outgoing_links_count = pages.at(incoming_link).getOutlinks().size();
            backlinks_scores[page] += 1.0 / (outgoing_links_count + 1);
        }
    }
    
    return backlinks_scores;
}

// document density calculation function
map<string, double> calculateDocumentDensity(const vector<string>& query, map<string, Soup>& pages) {
    map<string, vector<pair<string, int> > > wordDocuments;
    map<string, pair<int, int> > wordFrequency;

    // for each page, check if it contains any of the query words
    for (auto it = pages.begin(); it != pages.end();) {
        const string& pageUrl = it->first;
        Soup& soup = it->second;
        
        // If the page doesn't contain all query words, erase it from the map
        if (!containsAllWords(query, soup.getBody())) {
            it = pages.erase(it);
        } else {
            // If it contains all words, proceed with counting and calculating densities
            for (const auto& word : query) {
                int count = soup.getCount(word);
                wordDocuments[word].emplace_back(pageUrl, count);
                wordFrequency[word].first += count;
                wordFrequency[word].second += soup.getContent().size();
            }
            ++it; // Only increment the iterator if the page was not erased
        }
    }

    // calculate keyword density across all documents
    // For the first keyword in the query, calculate its overall frequency across all documents, and then divide this by the sum of the lengths of all documents.

    map<string, double> documentDensity;
    // how many times does keyword appear in document
    for (string word : query) {

        double density = wordFrequency[word].first / wordFrequency[word].second;

        // for each document that contains the keyword
        for (int j = 0; j < int(wordDocuments[word].size()); j++) {
            // calculate keyword density
            documentDensity[wordDocuments[word][j].first] += wordDocuments[word][j].second / (pages[wordDocuments[word][j].first].getContent().size() * density);
        }
    }

    return documentDensity;
}

bool compareScore(const pair<string, double>& a, const pair<string, double>& b) {
    // If scores are equal, sort by key to have a consistent order
    if (a.second == b.second) {
        return a.first < b.first;
    }
    // Otherwise, sort by score in descending order
    return a.second > b.second;
}

vector<pair<string, double>> sortMapByValue(const map<string, double>& page_scores) {
    // Create a vector of pairs and copy elements from the map
    vector<pair<string, double>> sorted_scores(begin(page_scores), end(page_scores));

    // Sort using the custom comparator
    sort(sorted_scores.begin(), sorted_scores.end(), compareScore);

    return sorted_scores;
}

void regularSearch(const vector<string>& query, map<string, Soup>& pages) {
    // remove pages that dont contain BOTH of the query words
    

    // get document density
    map<string, double> documentDensity = calculateDocumentDensity(query, pages);

    // get backlinks map
    map<string, vector<string> > backlinks_map = invertLinks(pages);

    // calculate backlinks score
    map<string, double> backlinks_scores = calculateBacklinksScore(backlinks_map, pages);

    // calculate page score only for non zero scores
    map<string, double> page_scores;

    for (const pair<string, Soup> pair : pages) {
        const string& page = pair.first;
        const Soup& soup = pair.second;
        double keyword_density_score = documentDensity[page];
        double backlinks_score = backlinks_scores[page];
        double page_score = 0.5 * keyword_density_score + 0.5 * backlinks_score;
        if (page_score > 0) {
            page_scores[page] = page_score;
        }
    }

    // sort page scores
    vector<pair<string, double> > sorted_page_scores = sortMapByValue(page_scores);

    // print all pages urls
    for (const pair<string, double>& pair : sorted_page_scores) {
        cout << pair.first << endl;
    }
}

int main(int argc, char* argv[]) {
    // check command line arguments len 4-6
    if (argc < 4 || argc > 6) {
        cout << "Usage: " << argv[0] << " <input file> <output file> <regular/phrase search 1-3>" << endl;
        return 1;
    }

    // recursively crawl the web
    // create a vector of Soup objects
    map<string, Soup> pages;
    
    if (argv[3][0] == '"' && argv[argc-1][strlen(argv[argc]) - 1] == '"') {
        // phrase search
        // remove quotes
        size_t quotePos;
        // unfortunately, autograder will pass \" to the command line, and thus the double quote will be a part of the string.
        for (int i = 4; i < argc; i++) {
            if ((quotePos = string(argv[i]).find('"')) != string::npos) {
                string(argv[i]).erase(quotePos, 1); // remove the double quote character at the found position; here number 1 as the second argument means erasing 1 character.
            }
        }

    } else {
        // regular search

    }
    
    cout << argv[3] << ' ' << argv[4] << endl;


    webCrawl("", argv[1], pages);

    cout << "done" << endl;

    regularSearch({"Boston", "Cruise"}, pages);

    cout << "done" << endl;

}