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
    // Implementation code here
}

void CommentNode::likeComment() {
    // Implementation code here
}

void CommentNode::deleteComment() {
    // Implementation code here
}

void CommentNode::displayComment(std::ostream &out) const {
    // Implementation code here
}

// Other necessary functions can be implemented here
