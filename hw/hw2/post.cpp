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
    return  getMessage() + " liked by " + std::to_string(getLikes()) + " people.\n";
}

std::string Post::getAuthor()
{
    return ""; 
}

bool Post::getIsPublic()
{
    return true;
}

// INCOMING POST FUNCTS

IncomingPost::IncomingPost()
{
    isPublic_ = true;
    author_ = "";
}

IncomingPost::IncomingPost(int messageId, int ownerId, std::string message, int likes, bool isPublic, std::string author) : Post(messageId, ownerId, message, likes) 
{
    isPublic_ = isPublic;
    author_ = author;
}

std::string IncomingPost::toString()
{
    std::string message = Post::toString();
    if(getIsPublic())
    {
        return getAuthor()  + " wrote: " + message;
    }
    else
    {
        return getAuthor() + " wrote (private): " + message;
    }
}

std::string IncomingPost::getAuthor()
{
    return author_;
}

bool IncomingPost::getIsPublic()
{
    return isPublic_;
}