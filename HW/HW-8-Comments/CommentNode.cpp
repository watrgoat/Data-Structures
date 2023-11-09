#include "CommentNode.h"
#include <iostream>

// Implement CommentNode member functions here
CommentNode::CommentNode(const std::string &vid_id, const std::string &auth, const std::string &comm_id,
                         int likes, int replies, bool is_rep, const std::string &parent_id,
                         const std::string &pub_date, const std::string &crawl_date, 
                         bool video_owner, const std::string &comment)
    : video_id(vid_id), author(auth), comment_id(comm_id), like_count(likes),
      reply_count(replies), is_reply(is_rep), parent_comment_id(parent_id),
      published_date(pub_date), crawled_date(crawl_date), is_video_owner(video_owner),
      comment_text(comment) {}

void CommentNode::addReply(const CommentNode &reply) {
    replies.push_back(reply);
    reply_count++;
}

void CommentNode::likeComment() {
    like_count++;
}

// @user1 0 seconds ago
// Friends is my favorite TV show. Thank you for all the laughs. I will always remember the character Chandler Bing.
// 👍 0
// 1 reply
void CommentNode::displayComment(std::ostream &out) const {
    out << author << " " << published_date << std::endl;
    out << comment_text << std::endl;
    out << "\U0001F44D " << like_count << std::endl;\
    out << reply_count << " replies" << std::endl;
}
