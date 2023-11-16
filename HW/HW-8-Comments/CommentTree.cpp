#include "CommentTree.h"
#include <iostream>
#include <fstream>
#include <sstream>

namespace {
    // removes all replies from lookup
    void removeRepliesFromLookup(std::unordered_map<std::string, CommentNode *>& commentLookup, CommentNode& comment) {
        for (CommentNode& reply : comment.getReplies()) {
            commentLookup.erase(reply.getCommentId());
            removeRepliesFromLookup(commentLookup, reply);
        }
    }
}

// constructor
CommentTree::CommentTree() {}

void CommentTree::updateLookup(CommentNode& comment) {
    commentLookup[comment.getCommentId()] = &comment;
}

CommentNode* CommentTree::findComment(const std::string& comment_id) {
    // Find the comment in the lookup map
    std::unordered_map<std::string, CommentNode *>::iterator it = commentLookup.find(comment_id);
    if (it != commentLookup.end()) {
        return it->second;
    }

    return nullptr;
}

CommentNode* CommentTree::findParent(CommentNode& root, const std::string& comment_id, CommentNode** parent) {
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

void CommentTree::addReplyToComment(const std::string& parent_id, const std::string& reply_id, const std::string& username, const std::string& reply_text) {
    // Find the parent comment
    CommentNode* parent = findComment(parent_id);
    if (!parent) {
        std::cerr << "Parent not found\n";
        return;
    }

    // create new comment
    CommentNode newNode(parent->getVideoId(), username, reply_id, 0, 0, true, parent_id, "0 seconds ago", "", false, reply_text);

    // add reply to parent
    parent->addReply(newNode);
    updateLookup(parent->getReplies().back());
}

void CommentTree::addReplyToVideo(const std::string& reply_id, const std::string& username, const std::string& reply_text) {
    // create new comment
    CommentNode newNode("", username, reply_id, 0, 0, true, "", "0 seconds ago", "", false, reply_text);

    // add reply to parent
    comments.push_back(newNode);
    updateLookup(comments.back());
}

void CommentTree::likeComment(const std::string& comment_id) {
    CommentNode* comment = findComment(comment_id);
    if (!comment) {
        std::cerr << "Comment not found\n";
        return;
    }
    comment->likeComment();
}

void CommentTree::displayComment(std::ofstream &outFile, const std::string& comment_id) {
    // Find the comment
    CommentNode* comment = findComment(comment_id);

    // display comment
    comment->displayComment(outFile);
}

void CommentTree::deleteComment(const std::string& comment_id) {
    for (std::vector<CommentNode>::iterator it = comments.begin(); it != comments.end();) {
        if (it->getCommentId() == comment_id) {
            removeRepliesFromLookup(commentLookup, *it);
            it = comments.erase(it);
            commentLookup.erase(comment_id);
            return; // If you expect only one comment with this ID
        } else {
            ++it;
        }
    }

    // Find the parent comment
    CommentNode* parent = nullptr;

    for (CommentNode& comment : comments) {
        findParent(comment, comment_id, &parent);
    }

    CommentNode* comment = findComment(comment_id);

    // remove comment and all replies from lookup
    removeRepliesFromLookup(commentLookup, *comment);

    commentLookup.erase(comment_id);

    // remove comment from parent
    parent->removeReply(comment_id);
}

void CommentTree::readJsonComments(std::ifstream &file) {
    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string key, value, discard;

        // temp vars to store the values
        std::string video_id, author, comment_id, parent_comment_id, published_date, crawled_date, comment;
        int like_count = 0, reply_count = 0;
        bool is_reply = false, is_video_owner = false;

        while (iss >> key) {
            if (key.back() != ':') continue; // Skip if it's not a key
            key.pop_back(); // Remove the colon

            if (key == "\"video_id\"" || key == "\"author\"" || key == "\"comment_id\"" || 
                key == "\"parent_comment_id\"" || key == "\"published_date\"" || 
                key == "\"crawled_date\"" || key == "\"comment\"") {
                iss >> std::ws; // Skip any whitespace

                if (iss.peek() == '"') {
                    // if the field starts with a double quote, read it as a whole string
                    iss.get();  // consume the opening double quote
                    std::getline(iss, value, '"');  // read until the closing double quote
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
            updateLookup(comments.back());
        } else {
            // Find the parent and add this node as a child
            // likely at the end of the vector
            if (comments.back().getCommentId() == newNode.getParentCommentId()) {
                comments.back().addReply(newNode);
                comments.back().decreaseReplyCount();

                updateLookup(comments.back().getReplies().back());
                continue;
            }

            for (CommentNode& comment : comments) {
                if (comment.getCommentId() == newNode.getParentCommentId()) {
                    comment.addReply(newNode);
                    comment.decreaseReplyCount();
                    updateLookup(comment.getReplies().back());
                    break;
                }
            }
        }
    }
}

void CommentTree::executeTextComments(std::ifstream &file, std::ofstream &outFile) {
    std::string line;

    while (getline(file, line)) {
        std::istringstream iss(line);
        std::string command, parent_id, id, user, comment_text;

        iss >> command;
        
        // reply_to_comment <parent_id> <reply_id> <username> <reply_text>
        if (command == "reply_to_comment") {
            iss >> parent_id >> id >> user;
            iss >> std::ws; // Skip any whitespace
            if (iss.peek() == '"') {
                iss.get(); // Consume the opening double quote
                getline(iss, comment_text, '"'); // Read until the closing double quote
            }
            
            addReplyToComment(parent_id, id, user, comment_text);

        // reply_to_video <user_id> <username> <reply_text>
        } else if (command == "reply_to_video") {
            iss >> id >> user; // Assuming id here is the video id
            iss >> std::ws; // Skip any whitespace
            if (iss.peek() == '"') {
                iss.get(); // Consume the opening double quote
                getline(iss, comment_text, '"'); // Read until the closing double quote
            }
            
            addReplyToVideo(id, user, comment_text);

        // like_comment <comment_id>
        } else if (command == "like_comment") {
            iss >> id;
            
            likeComment(id);

        // delete_comment <comment_id>
        } else if (command == "delete_comment") {
            iss >> id;
            
            deleteComment(id);

        // display_comment <comment_id>
        } else if (command == "display_comment") {
            iss >> id;
            
            displayComment(outFile, id);

        // Unknown command handling
        } else {
            std::cerr << "Unknown command: " << command << std::endl;
        }
    }
}
