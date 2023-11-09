/*
Makes youtube comments like reddit comments!!
*/

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iomanip>
#include "CommentNode.h"

using namespace std;

// Function Prototypes
void readJsonComments(ifstream &file, vector<CommentNode>& comments);
void readTextComments(ifstream &file, vector<CommentNode>& comments);
void deleteComment(vector<CommentNode>& comments, string comment_id);

// example json: {"video_id": "qExVlz3zb0k", "author": "@wolf-pubgmobile429", "comment_id": "Ugxx0s9GNAbYt-EhbAl4AaABAg.9gVKNLvt7VJ9gVM3k4FEoy", "like_count": 12, "reply_count": 0, "is_reply": true, "parent_comment_id": "Ugxx0s9GNAbYt-EhbAl4AaABAg", "published_date": "1 year ago", "crawled_date": "2023-10-29T21:26:39.024635", "is_video_owner": false, "comment": "No her instagram story and post so weird and sick!"}


void readJsonComments(std::ifstream &file, std::vector<CommentNode>& comments) {
    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string key, value, discard;

        // Temporary variables for storing the parsed data
        std::string video_id, author, comment_id, parent_comment_id, published_date, crawled_date, comment;
        int like_count = 0, reply_count = 0;
        bool is_reply = false, is_video_owner = false;

        while (iss >> key) {
            if (key.back() != ':') continue; // Skip if it's not a key
            key.pop_back(); // Remove the colon

            if (key == "\"video_id\"" || key == "\"author\"" || key == "\"comment_id\"" || 
                key == "\"parent_comment_id\"" || key == "\"published_date\"" || 
                key == "\"crawled_date\"" || key == "\"comment\"") {
                iss >> std::quoted(value);
                if (key == "\"video_id\"") video_id = value;
                else if (key == "\"author\"") author = value;
                else if (key == "\"comment_id\"") comment_id = value;
                else if (key == "\"parent_comment_id\"") parent_comment_id = value;
                else if (key == "\"published_date\"") published_date = value;
                else if (key == "\"crawled_date\"") crawled_date = value;
                else if (key == "\"comment\"") comment = value;
            } else if (key == "\"like_count\"" || key == "\"reply_count\"") {
                int intValue;
                iss >> intValue;
                if (key == "\"like_count\"") like_count = intValue;
                else if (key == "\"reply_count\"") reply_count = intValue;
            } else if (key == "\"is_reply\"" || key == "\"is_video_owner\"") {
                bool boolValue;
                iss >> std::boolalpha >> boolValue;
                if (key == "\"is_reply\"") is_reply = boolValue;
                else if (key == "\"is_video_owner\"") is_video_owner = boolValue;
            } else {
                iss >> discard; // Discard the value of an unknown or unused key
            }
        }

        // Create a new CommentNode instance using the extracted values
        CommentNode newNode(video_id, author, comment_id, like_count, reply_count,
                            is_reply, parent_comment_id, published_date, crawled_date,
                            is_video_owner, comment);

        if (!newNode.isReply()) {
            comments.push_back(newNode);
        } else {
            // Find the parent and add this node as a child
            for (CommentNode& comment : comments) {
                if (comment.getCommentId() == newNode.getParentCommentId()) {
                    comment.addReply(newNode);
                    break;
                }
            }
        }
    }
}
void readTextComments(ifstream &file, vector<CommentNode>& comments) {
    
}

int main(int argc, char* argv[]) {
    // check input arg len
    if (argc != 4) {
        cerr << "Usage: ./run <input_json> <input_text> <output_text>" << endl;
    }

    // open json file
    ifstream json_file(argv[1]);

    // read in json comments
    vector<CommentNode> comments;
    readJsonComments(json_file, comments);
}