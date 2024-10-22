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
    return "hello"; // something
}

bool getIsPublic()
{
    return true; // true/false based on something
}
