#include "post.h"
#include <sstream>

// default constuctor
Post::Post() {};

Post::Post(int messageId, int ownerId, std::string message, int likes)
{
    messageId_ = messageId; // id of the message
    ownerId_ = ownerId; // id of the user who posted
    message_ = message; // holds content of the post
    likes_ = likes; // counts no. of users who have liked post
}

// GETTERS

int Post::getMessageId()
{
    return messageId_;
}

int Post::getOwnerId()
{
    return ownerId_;
}

std::string Post::getMessage()
{
    return message_;
}

int Post::getLikes()
{
    return likes_;
}

std::string Post::toString()
{
    std::ostringstream oss; // have to build a string to return
    oss << message_ << "Liked by " << likes_ << " people.";
    return oss.str();
}

std::string Post::getAuthor()
{
    return ""; // something
}

bool Post::getIsPublic()
{
    return true; // true/false based on something
}


IncomingPost::IncomingPost()
{
    isPublic_ = true;
    author_ = " ";
}
/*
IncomingPost::IncomingPost(int messageId, int ownerId, std::string message, int likes, bool isPublic, std::string author) : Post(messageId, ownerId, message, likes) 
{
    isPublic_ = isPublic;
    author_ = author;
}
*/