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

CommentNode* findCommentNode(CommentNode& root, const string& comment_id);
CommentNode* findCommentAll(vector<CommentNode>& comments, const string& comment_id);

void addReplyToComment(vector<CommentNode>& comments, string parent_id, string reply_id, string username, string reply_text);
void addReplyToVideo(vector<CommentNode>& comments, string reply_id, string username, string reply_text);
void likeComment(vector<CommentNode>& comments, string comment_id);
void displayComment(ofstream &outFile, vector<CommentNode>& comments, string comment_id);
void deleteComment(vector<CommentNode>& comments, const string& comment_id);

void executeTextComments(ifstream &file, ofstream &outFile, vector<CommentNode>& comments);


// reads in json comments adds to tree structure
void readJsonComments(ifstream &file, vector<CommentNode>& comments) {
    string line;
    while (getline(file, line)) {
        istringstream iss(line);
        string key, value, discard;

        // temp vars to store the values
        string video_id, author, comment_id, parent_comment_id, published_date, crawled_date, comment;
        int like_count = 0, reply_count = 0;
        bool is_reply = false, is_video_owner = false;

        while (iss >> key) {
            if (key.back() != ':') continue; // Skip if it's not a key
            key.pop_back(); // Remove the colon

            if (key == "\"video_id\"" || key == "\"author\"" || key == "\"comment_id\"" || 
                key == "\"parent_comment_id\"" || key == "\"published_date\"" || 
                key == "\"crawled_date\"" || key == "\"comment\"") {
                iss >> ws; // Skip any whitespace

                if (iss.peek() == '"') {
                    // if the field starts with a double quote, read it as a whole string
                    iss.get();  // consume the opening double quote
                    getline(iss, value, '"');  // read until the closing double quote
                    // iss >> comment;  // read the quoted field
                    if (!value.empty() && value.back() == '"') {
                        value.pop_back();  // remove the closing double quote
                    }
                }

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
                iss >> boolalpha >> boolValue;
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
            // likely at the end of the vector
            if (comments.back().getCommentId() == newNode.getParentCommentId()) {
                comments.back().addReply(newNode);
                comments.back().decreaseReplyCount();
                continue;
            }

            for (CommentNode& comment : comments) {
                if (comment.getCommentId() == newNode.getParentCommentId()) {
                    comment.addReply(newNode);
                    comment.decreaseReplyCount();
                    break;
                }
            }
        }
    }
}

// helper function to find comment with given id
CommentNode* findCommentNode(CommentNode& root, const string& comment_id) {
    // check if curr id matches target id
    if (root.getCommentId() == comment_id) {
        return &root;
    }

    // cearch through all replies
    for (CommentNode& reply : root.getReplies()) {
        CommentNode* found = findCommentNode(reply, comment_id);
        if (found != nullptr) {
            return found;
        }
    }

    return nullptr;
}

// finds the comment with the given ID and adds a reply to it
CommentNode* findCommentAll(vector<CommentNode>& comments, const string& comment_id) {
    for (CommentNode& comment : comments) {
        CommentNode* found = findCommentNode(comment, comment_id);
        if (found != nullptr) {
            return found;
        }
    }
    return nullptr;
}

void addReplyToComment(vector<CommentNode>& comments, string parent_id, string reply_id, string username, string reply_text) {
    // find parent comment
    CommentNode* parent = findCommentAll(comments, parent_id);
    if (parent == nullptr) {
        cerr << "Error: Parent comment with ID '" << parent_id << "' not found." << endl;
        return;
    }

    // create new comment
    CommentNode newNode(parent->getVideoId(), username, reply_id, 0, 0, true, parent_id, "0 seconds ago", "", false, reply_text);

    // add reply to parent
    parent->addReply(newNode);
}

void addReplyToVideo(vector<CommentNode>& comments, string reply_id, string username, string reply_text) {
    // get video id
    string video_id = comments[0].getVideoId();

    // create new comment
    CommentNode newNode(video_id, username, reply_id, 0, 0, false, "", "0 seconds ago", "", false, reply_text);
    
    // add reply to comments
    comments.push_back(newNode);
}

void likeComment(vector<CommentNode>& comments, string comment_id) {
    // find comment
    CommentNode* comment = findCommentAll(comments, comment_id);
    if (comment == nullptr) {
        cerr << "Error: Comment with ID '" << comment_id << "' not found." << endl;
        return;
    }

    // like comment
    comment->likeComment();
}

void displayComment(ofstream &outFile, vector<CommentNode>& comments, string comment_id) {
    // find comment
    CommentNode* comment = findCommentAll(comments, comment_id);
    if (comment == nullptr) {
        cerr << "Error: Comment with ID '" << comment_id << "' not found." << endl;
        return;
    }

    // display comment
    comment->displayComment(outFile);
}

// helper for finding parent of comment
CommentNode* findParent(CommentNode& root, const string& comment_id, CommentNode** parent) {
    for (CommentNode& reply : root.getReplies()) {
        if (reply.getCommentId() == comment_id) {
            *parent = &root;
            return &reply;
        }
        CommentNode* found = findParent(reply, comment_id, parent);
        if (found != nullptr) {
            return found;
        }
    }
    return nullptr;
}

void deleteComment(vector<CommentNode>& comments, const string& comment_id) {
    // check if in root comments and remove
    for (vector<CommentNode>::iterator it = comments.begin(); it != comments.end(); ++it) {
        if (it->getCommentId() == comment_id) {
            comments.erase(it);
        }
    }

    // if not in the root comments, find the parent and delete the comment
    CommentNode* parent = nullptr;
    for (CommentNode& comment : comments) {
        CommentNode* found = findParent(comment, comment_id, &parent);
        if (found != nullptr && parent != nullptr) {
            // remove the comment
            parent->removeReply(comment_id);
            break;
        }
    }
}

// reads in text commands and executes them
void executeTextComments(ifstream &file, ofstream &outFile, vector<CommentNode>& comments) {
    string line;

    while (getline(file, line)) {
        istringstream iss(line);
        string command, parent_id, id, user, comment_text;

        iss >> command;
        
        // reply_to_comment <parent_id> <reply_id> <username> <reply_text>
        if (command == "reply_to_comment") {
            iss >> parent_id >> id >> user;
            iss >> ws; // Skip any whitespace
            if (iss.peek() == '"') {
                iss.get(); // Consume the opening double quote
                getline(iss, comment_text, '"'); // Read until the closing double quote
            }
            
            addReplyToComment(comments, parent_id, id, user, comment_text);

        // reply_to_video <user_id> <username> <reply_text>
        } else if (command == "reply_to_video") {
            iss >> id >> user; // Assuming id here is the video id
            iss >> ws; // Skip any whitespace
            if (iss.peek() == '"') {
                iss.get(); // Consume the opening double quote
                getline(iss, comment_text, '"'); // Read until the closing double quote
            }
            
            addReplyToVideo(comments, id, user, comment_text);

        // like_comment <comment_id>
        } else if (command == "like_comment") {
            iss >> id;
            
            likeComment(comments, id);

        // delete_comment <comment_id>
        } else if (command == "delete_comment") {
            iss >> id;
            
            deleteComment(comments, id);

        // display_comment <comment_id>
        } else if (command == "display_comment") {
            iss >> id;
            
            displayComment(outFile, comments, id);

        // Unknown command handling
        } else {
            cerr << "Unknown command: " << command << endl;
        }
    }
}


int main(int argc, char* argv[]) {
    // check input arg len
    if (argc != 4) {
        cerr << "Usage: ./run <input_json> <input_text> <output_text>" << endl;
    }

    // open json file
    ifstream json_file(argv[1]);
    if (!json_file.is_open()) {
        cerr << "Error: Cannot open file '" << argv[1] << "'." << endl;
        return 1;
    }

    // read in json comments
    vector<CommentNode> comments;
    readJsonComments(json_file, comments);

    // close json file
    json_file.close();

    // open text file
    ifstream text_file(argv[2]);
    if (!text_file.is_open()) {
        cerr << "Error: Cannot open file '" << argv[2] << "'." << endl;
        return 1;
    }

    // open output file
    ofstream out_file(argv[3]);
    if (!out_file.is_open()) {
        cerr << "Error: Cannot open file '" << argv[3] << "'." << endl;
        return 1;
    }

    // execute text comments
    executeTextComments(text_file, out_file, comments);

    // close files
    text_file.close();
    out_file.close();
    // ./run.exe hold_me_closer.json input1_hold_me_closer.txt output.txt
    return 0;
}