#include "Soup.h"

namespace {
    string findTitle(const string &content) {
        // regular expression to match title tag
        regex titleRegex("<title>(.+)</title>");
        smatch match;

        // search for title in the HTML content
        string::const_iterator start = content.cbegin();
        if (regex_search(start, content.cend(), match, titleRegex)) {
            // second match group contains the title
            if (match.size() > 1) {
                return match[1].str();
            }
        }
        return "";
    }

    // function to parse an HTML file and extract links to local files
    vector<string> extractLinksFromHTML(const string& content) {
        vector<string> links;
        // regular expression to match href attributes in anchor tags
        regex linkRegex("<a\\s+[^>]*href\\s*=\\s*['\"]([^'\"]+)['\"][^>]*>");
        smatch match;

        // search for links in the HTML content
        string::const_iterator start = content.cbegin();
        while (regex_search(start, content.cend(), match, linkRegex)) {
            if (match.size() > 1) {
                links.push_back(match[1].str());
            }
            start = match.suffix().first;
        }

        return links;
    }

    set<string> extractBody(const string& content) {
        set<string> words;
        regex bodyRegex("<body[^>]*>([\\s\\S]*?)</body>");
        smatch match;

        // Search for body in the HTML content
        if (regex_search(content, match, bodyRegex)) {
            // The first sub-match is the content of the body tag
            string bodyContent = match[1].str();
            
            // Use istringstream to split the bodyContent by whitespace
            istringstream iss(bodyContent);
            string word;
            while (iss >> word) {
                // Insert each word into the set
                words.insert(word);
            }
        }
        return words;
    }
}

// default constructor
Soup::Soup() 
    : title_(""),
      content_(""),
      outlinks_(),
      body_()
{}

// constructor with content
Soup::Soup(const string& content)
    : title_(findTitle(content)),
      content_(content),
      outlinks_(extractLinksFromHTML(content)),
      body_(extractBody(content))
{}

// copy constructor
Soup::Soup(const Soup& other)
    : title_(other.title_),
      content_(other.content_),
      outlinks_(other.outlinks_),
      body_(other.body_)
{}

// move constructor
Soup::Soup(Soup&& other) noexcept
    : title_(move(other.title_)),
      content_(move(other.content_)),
      outlinks_(move(other.outlinks_)),
      body_(move(other.body_))
{}

Soup& Soup::operator=(const Soup& other) {
    if (this != &other) {
        title_ = other.title_;
        content_ = other.content_;
        outlinks_ = other.outlinks_;
        body_ = other.body_;
    }
    return *this;
}

bool Soup::operator==(const Soup& other) const {
    // check content
    if (content_ != other.getContent()) {
        return false;
    }
    return true;
}

bool Soup::operator!=(const Soup& other) const {
    return !(*this == other);
}

bool Soup::operator<(const Soup& other) const {
    // check count
    if (content_.size() < other.getContent().size()) {
        return true;
    }
    return false;
}

bool Soup::operator>(const Soup& other) const {
    return !(*this < other);
}

// getters
string Soup::getTitle() const {
    return title_;
}

string Soup::getContent() const {
    return content_;
}

vector<string> Soup::getOutlinks() const {
    return outlinks_;
}

set<string> Soup::getBody() const {
    return body_;
}

int Soup::getCount(string word) const {
    int count = 0;

    for (size_t i = 0; i <= content_.size() - word.size(); i++) {
        // Check if the word matches at the current position
        bool match = true;
        for (size_t j = 0; j < word.size(); j++) {
            if (content_[i + j] != word[j]) {
                match = false;
                break;
            }
        }
        // If every character matched, increment count
        if (match) {
            count++;
        }
    }

    return count;
}

// edit links
void Soup::addOutlink(const string& outlink) {
    outlinks_.push_back(outlink);
}

void Soup::removeOutlink(const string& outlink) {
    for (int i = 0; i < int(outlinks_.size()); i++) {
        if (outlinks_.at(i) == outlink) {
            outlinks_.erase(outlinks_.begin() + i);
        }
    }
}