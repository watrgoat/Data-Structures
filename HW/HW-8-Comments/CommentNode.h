#ifndef COMMENTNODE_H
#define COMMENTNODE_H

#include <string>
#include <vector>

class CommentNode {
public:
    std::string video_id;
    std::string author;
    std::string comment_id;
    int like_count;
    int reply_count;
    bool is_reply;
    std::string parent_comment_id;
    std::string published_date;
    std::string crawled_date;
    bool is_video_owner;
    std::string comment_text;
    std::vector<CommentNode> replies; // Nested child comments

    // Constructor
    CommentNode(const std::string &vid_id, const std::string &auth, const std::string &comm_id,
                int likes, int replies, bool is_rep, const std::string &parent_id,
                const std::string &pub_date, const std::string &crawl_date, 
                bool video_owner, const std::string &comment);

    // Functions for manipulating comments
    void addReply(const CommentNode &reply);
    void likeComment();
    void deleteComment(); // This will need to recursively delete child comments
    void displayComment(std::ostream &out) const; // For nested display

    int numReplies() const { return replies.size(); }

    // Getters
    std::string getVideoId() const { return video_id; }
    std::string getAuthor() const { return author; }
    std::string getCommentId() const { return comment_id; }
    int getLikeCount() const { return like_count; }
    int getReplyCount() const { return reply_count; }
    bool isReply() const { return is_reply; }
    std::string getParentCommentId() const { return parent_comment_id; }
    std::string getPublishedDate() const { return published_date; }
    std::string getCrawledDate() const { return crawled_date; }
    bool isVideoOwner() const { return is_video_owner; }
    std::string getCommentText() const { return comment_text; }
    std::vector<CommentNode> getReplies() const { return replies; }
};

#endif // COMMENTNODE_H
