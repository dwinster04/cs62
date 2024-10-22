#include "post.h"


Post::Post() {};

Post::Post(int messageId, int ownerId, std::string message, int likes)
{
    messageId_ = messageId; // id of the message
    ownerId_ = ownerId; // id of the user who posted
    message_ = message; // holds content of the post
    likes_ = likes; // counts no. of users who have liked post
}

std::string Post::toString(std::string message, std::string likes)
{
    std::cout << message << "Liked by " << likes << "people." << std::endl;
}