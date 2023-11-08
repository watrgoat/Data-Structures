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

    // Split base path into parts
    while (getline(baseStream, temp, '/')) {
        if (temp != "." && !temp.empty()) {
            baseParts.push_back(temp);
        }
    }

    // Split relative path into parts
    while (getline(relativeStream, temp, '/')) {
        if (temp == "..") {
            if (!baseParts.empty()) {
                baseParts.pop_back();
            }
        } else if (temp != "." && !temp.empty()) {
            relativeParts.push_back(temp);
        }
    }

    // Combine the parts into a single path
    ostringstream resolvedPath;
    if (basePath.front() == '/') {
        resolvedPath << '/';
    }
    for (const auto& part : baseParts) {
        resolvedPath << part << "/";
    }
    for (const auto& part : relativeParts) {
        resolvedPath << part << "/";
    }

    string resolved = resolvedPath.str();
    if (!resolved.empty() && resolved.back() == '/') {
        resolved.pop_back(); // Remove trailing slash if necessary
    }

    return resolved;
}

Soup readFileIntoSoup(const string& path) {
    ifstream fileStream(path);
    if (!fileStream.is_open()) {
        cerr << "Could not open the file - '" << path << "'" << endl;
        exit(1);
    }
    string fileContent((istreambuf_iterator<char>(fileStream)), istreambuf_iterator<char>());
    Soup soup(fileContent);
    return soup;
}

void webCrawl(const string& basePath, const string& url, map<string, Soup>& pages) {
    // Resolve the relative path
    string resolvedPath = resolvePath(basePath, url);
    // Check if path isn't in pages
    if (pages.find(resolvedPath) == pages.end()) {
        pages[resolvedPath] = readFileIntoSoup(resolvedPath);

        for (const string& relativePath : pages[resolvedPath].getOutlinks()) {
            // Construct new base path by removing the file name from the resolved path
            string newBasePath = resolvedPath.substr(0, resolvedPath.find_last_of('/'));
            webCrawl(newBasePath, relativePath, pages);
        }
    }
}

map<string, vector<string>> invertLinks(const map<string, Soup>& pages) {
    map<string, vector<string>> backlinks_map;

    for (const auto& pair : pages) {
        const string& pageUrl = pair.first; // pageUrl is the resolved path of the current page
        const vector<string>& outgoing_links = pair.second.getOutlinks();
        
        // Base path for outlinks will be the directory of the current page
        string basePath = pageUrl.substr(0, pageUrl.find_last_of('/'));

        for (const string& relative_link : outgoing_links) {
            // Resolve each relative outlink to an absolute path
            string absoluteOutlink = resolvePath(basePath, relative_link);
            backlinks_map[absoluteOutlink].push_back(pageUrl);
        }
    }
    
    return backlinks_map;
}

bool containsAllWords(const vector<string>& query, const set<string>& body) {
    return all_of(query.begin(), query.end(), [&](const string& word) {
        return body.find(word) != body.end();
    });
}

map<string, double> calculateBacklinksScore(const map<string, vector<string>>& backlinks_map, const map<string, Soup>& pages) {
    map<string, double> backlinks_scores;
    
    // Initialize backlink scores to zero for all pages
    for (const auto& pair : pages) {
        backlinks_scores[pair.first] = 0.0;
    }

    // Calculate backlink scores
    for (const auto& pair : backlinks_map) {
        const string& page = pair.first;
        const vector<string>& incoming_links = pair.second;
        
        for (const string& incoming_link : incoming_links) {
            if (pages.count(incoming_link)) {  // Check if the incoming link is a valid page
                unsigned int outgoing_links_count = pages.at(incoming_link).getOutlinks().size();
                backlinks_scores[page] += 1.0 / (outgoing_links_count + 1);
            }
        }
    }
    
    return backlinks_scores;
}

// document density calculation function
map<string, double> calculateDocumentDensity(const vector<string>& query, const map<string, Soup>& pages) {
    map<string, double> documentDensity;
    map<string, int> totalWordCounts;
    int totalContentLength = 0;

    // First, we calculate the total number of occurrences and total content length for each keyword
    for (const auto& pagePair : pages) {
        totalContentLength += pagePair.second.getContent().length();
        for (const string& word : query) {
            totalWordCounts[word] += pagePair.second.getCount(word);
        }
    }

    // Then, we calculate the keyword density score for each document
    for (const auto& pagePair : pages) {
        const string& url = pagePair.first;
        const Soup& soup = pagePair.second;
        const string content = soup.getContent();
        double score = 0.0;

        for (const string& word : query) {
            int wordCount = soup.getCount(word);
            double keywordDensity = wordCount / static_cast<double>(content.length());
            double keywordDensityAcrossDocuments = static_cast<double>(totalWordCounts[word]) / totalContentLength;
            score += keywordDensity / keywordDensityAcrossDocuments;
        }
        documentDensity[url] = score;
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
    vector<pair<string, double>> sorted_scores(begin(page_scores), end(page_scores));
    sort(sorted_scores.begin(), sorted_scores.end(), compareScore);
    return sorted_scores;
}

string getSnippetFromContent(const string& content, const string& searchText) {

    // Find the first occurrence of searchText
    size_t searchTextPos = content.find(searchText);
    if (searchTextPos == string::npos) {
        return ""; // Search text not found
    }

    // Find the last period before the searchText
    size_t periodPos = content.rfind('.', searchTextPos);
    if (periodPos == string::npos || periodPos < searchTextPos - 120) {
        periodPos = searchTextPos > 120 ? searchTextPos - 120 : 0;
    } else {
        // Move one character ahead to not include the period itself
        periodPos += 1;
    }

    // Get the snippet, ensuring not to go beyond the bounds of the string
    size_t snippetLength = (content.length() - periodPos < 120) ? content.length() - periodPos : 120;
    string snippet = content.substr(periodPos, snippetLength);

    return snippet;
}

void regularSearch(ofstream &out, const vector<string>& query, map<string, Soup>& pages) {

    // Get document density
    map<string, double> documentDensity = calculateDocumentDensity(query, pages);

    // Get backlinks map
    map<string, vector<string>> backlinks_map = invertLinks(pages);

    // Calculate backlinks score
    map<string, double> backlinks_scores = calculateBacklinksScore(backlinks_map, pages);

    // remove pages with no keyword matches
    for (auto it = pages.begin(); it != pages.end();) {
        if (!containsAllWords(query, it->second.getBody())) {
            it = pages.erase(it);
        } else {
            ++it;
        }
    }

    // Calculate page score only for non-zero scores
    map<string, double> page_scores;
    for (const auto& page_pair : pages) {
        double keyword_density_score = documentDensity[page_pair.first];
        double backlinks_score = backlinks_scores[page_pair.first];
        double page_score = 0.5 * keyword_density_score + 0.5 * backlinks_score;
        page_scores[page_pair.first] = page_score;
    }

    // Sort page scores
    vector<pair<string, double>> sorted_page_scores = sortMapByValue(page_scores);
    
    out << "Matching documents:" << endl << endl;

    // Print all pages URLs
    for (const auto& pair : sorted_page_scores) {
        // soup title
        out << "Title: " << pages[pair.first].getTitle() << endl;
        out << "Url: " << pair.first << endl;
        out << "Description: " << pages[pair.first].getDescription() << endl;
        out << "Snippet: " << getSnippetFromContent(pages[pair.first].getContent(), query[0]) << endl;
        out << endl;
    }
}

void phraseSearch(ofstream &out, const vector<string>& query, map<string, Soup>& pages) {

    string searchPhrase;
    for (const auto& word : query) {
        if (!searchPhrase.empty()) searchPhrase += " "; // Add space before the next word
        searchPhrase += word;
    }

    // Get document density
    map<string, double> documentDensity = calculateDocumentDensity(query, pages);

    // Get backlinks map
    map<string, vector<string>> backlinks_map = invertLinks(pages);

    // Calculate backlinks score
    map<string, double> backlinks_scores = calculateBacklinksScore(backlinks_map, pages);

    // remove pages with no keyword matches and pages that do not contain the entire search phrase
    for (auto it = pages.begin(); it != pages.end();) {
        bool hasAllWords = containsAllWords(query, it->second.getBody());
        bool containsPhrase = (it->second.getContent().find(searchPhrase) != string::npos); // Check if the entire phrase exists

        if (!hasAllWords || !containsPhrase) {
            cout << "Removing page: " << it->first << endl;
            it = pages.erase(it); // Remove pages that do not meet both conditions
        } else {
            ++it; // Only increment if we didn't erase
        }
    }

    // Calculate page score only for non-zero scores
    map<string, double> page_scores;
    for (const auto& page_pair : pages) {
        double keyword_density_score = documentDensity[page_pair.first];
        double backlinks_score = backlinks_scores[page_pair.first];
        double page_score = 0.5 * keyword_density_score + 0.5 * backlinks_score;
        page_scores[page_pair.first] = page_score;
    }

    // Sort page scores
    vector<pair<string, double>> sorted_page_scores = sortMapByValue(page_scores);
    
    out << "Matching documents:" << endl << endl;

    // Print all pages URLs
    for (const auto& pair : sorted_page_scores) {
        // soup title
        out << "Title: " << pages[pair.first].getTitle() << endl;
        out << "Url: " << pair.first << endl;
        out << "Description: " << pages[pair.first].getDescription() << endl;
        // snippet
        // todo
        out << endl;
    }
}

int main(int argc, char* argv[]) {
    // check command line arguments len 4-6
    if (argc < 4 || argc > 6) {
        cout << "Usage: " << argv[0] << " <input file> <output file> <regular/phrase search 1-3>" << endl;
        return 1;
    }

    // open output file
    ofstream out(argv[2]);
    if (!out.is_open()) {
        cerr << "Could not open the file - '" << argv[2] << "'" << endl;
        return 1;
    }

    // recursively crawl the web
    map<string, Soup> pages;

    webCrawl("", argv[1], pages);
    
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
        vector<string> searchTerms;
        for (int i = 3; i < argc; i++) {
            searchTerms.push_back(argv[i]);
        }

        phraseSearch(out, searchTerms, pages);

    } else {
        // regular search
        // get vector of search terms
        vector<string> searchTerms;
        for (int i = 3; i < argc; i++) {
            searchTerms.push_back(argv[i]);
        }
        regularSearch(out, searchTerms, pages);
    }
}