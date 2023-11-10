#ifndef COMMENTTREE_H
#define COMMENTTREE_H

#include "CommentNode.h"
#include <vector>
#include <unordered_map>
#include <string>
#include <fstream>

class CommentTree {
public:
    CommentTree();

    void readJsonComments(ifstream &file)
    void executeTextComments(std::ifstream &file, std::ofstream &outFile);

private:
    std::vector<CommentNode> comments;
    std::unordered_map<std::string, CommentNode*> commentLookup;

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
};

#endif // COMMENTTREE_H
