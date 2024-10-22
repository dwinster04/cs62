#ifndef POST_H
#define POST_H

#include <vector>
#include "user.h"
#include "network.h"

// class Post

class Post
{
private:
    int messageId_; 
    int ownerId_;
    std::string message_;
    int likes_;

public:
    // default constructor
    
    // pre: none
    // post: creates an empty object post
    Post();

    // pre: none
    // post: creates parameterized object
    Post(int messageId, int ownerId, std::string message, int likes);

    // pre: none
    // post: return a message showing [messageId] liked by [likes_] people.
    std::string toString(std::string message, std::string likes);

};

















#endif // POST_H