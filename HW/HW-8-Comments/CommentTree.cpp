#include "CommentTree.h"
#include <iostream>

void readJsonComments(ifstream &file)
void executeTextComments(std::ifstream &file, std::ofstream &outFile);

CommentNode* findCommentNode(CommentNode& root, const std::string& comment_id);
CommentNode* findCommentAll(const std::string& comment_id);
CommentNode* findParent(CommentNode& root, const std::string& comment_id, CommentNode** parent);
void updateLookup(CommentNode& comment);

void addReplyToComment(const std::string& parent_id, const std::string& reply_id, 
                        const std::string& username, const std::string& reply_text);
void addReplyToVideo(const std::string& reply_id, const std::string& username, 
                        const std::string& reply_text);
void likeComment(const std::string& comment_id);
void displayComment(std::ofstream &outFile, const std::string& comment_id);
void deleteComment(const std::string& comment_id);

void CommentTree::addReplyToComment(const std::string& parent_id, const std::string& reply_id, 
                                    const std::string& username, const std::string& reply_text) {
    // Implementation similar to your current addReplyToComment
    // Make sure to update the commentLookup map
}

// Implement other methods similarly

void CommentTree::updateLookup(CommentNode& comment) {
    commentLookup[comment.getCommentId()] = &comment;
    for (auto& reply : comment.getReplies()) {
        updateLookup(reply);
    }
}

// ... Other private helper methods ...
