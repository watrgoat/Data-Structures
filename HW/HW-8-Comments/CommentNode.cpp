#include "CommentNode.h"
#include <iostream>

namespace {
    void displayCommentHelper(std::ostream &out, const CommentNode &comment, int indent) {
        // Get the indent size string
        std::string indentStr(indent * 4, ' ');

        out << indentStr << comment.getAuthor() << " " << comment.getPublishedDate() << std::endl;
        out << indentStr << comment.getCommentText() << std::endl;
        out << indentStr << "\U0001F44D " << comment.getLikeCount() << std::endl;

        if (comment.getReplyCount() > 0) {
            out << indentStr << comment.getReplyCount() << " replies" << std::endl;
        }
        
        // calls function on each reply recursively
        for (const CommentNode &reply : comment.getReplies()) {
            displayCommentHelper(out, reply, indent + 1);
        }
    }
}

// Implement CommentNode member functions here
CommentNode::CommentNode(const std::string &vid_id, const std::string &auth, const std::string &comm_id,
                         int likes, int reply_ct, bool is_rep, const std::string &parent_id,
                         const std::string &pub_date, const std::string &crawl_date, 
                         bool video_owner, const std::string &comment)
    : video_id(vid_id), author(auth), comment_id(comm_id), like_count(likes),
      reply_count(reply_ct), is_reply(is_rep), parent_comment_id(parent_id),
      published_date(pub_date), crawled_date(crawl_date), is_video_owner(video_owner),
      comment_text(comment) {}

void CommentNode::addReply(const CommentNode &reply) {
    replies.push_back(reply);
    reply_count++;
}

void CommentNode::removeReply(const std::string &reply_id) {
    for (int i = 0; i < int(replies.size()); i++) {
        if (replies[i].getCommentId() == reply_id) {
            replies.erase(replies.begin() + i);
            reply_count--;
            break;
        }
    }
}

void CommentNode::likeComment() {
    like_count++;
}

// Displays the comment and all of its replies recursively
void CommentNode::displayComment(std::ostream &out) const {
    displayCommentHelper(out, *this, 0);
}
