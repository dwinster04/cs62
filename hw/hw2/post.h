#ifndef POST_H
#define POST_H

#include <vector>
#include "user.h"
#include "network.h"

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

    // GETTERS

    // pre: none
    // post: returns message id 
    int getMessageId();

    // pre: none
    // post: returns owner (of post) id
    int getOwnerId();

    // pre: none
    // post: returns content of the post
    std::string getMessage();

    // pre: none
    // post: returns number of likes on a post
    int getLikes();

    // pre: none
    // post: return a message showing [messageId] liked by [likes_] people.
    virtual std::string toString();

    // pre: none
    // post: returns author of the post
    virtual std::string getAuthor();

    // pre: none
    // post: returns true if its public
    virtual bool getIsPublic();

};
class IncomingPost: public Post
{
private:
    bool isPublic_;
    std::string author_;

public:
    // default constructor

    // pre: none
    // post: creates empty incoming post object
    IncomingPost();

    // pre: none
    // post: creates parameterized incoming post object
    IncomingPost(int messageId, int ownerId, std::string message, int likes, bool isPublic, std::string author);

    // pre: none
    // post: returns message saying who wrote something and states whether private or not
    std::string toString();

    // GETTERS

    // pre: none
    // post: returns the author of incoming post
    std::string getAuthor();

    // pre: none
    // post: returns T/F if post is public or not
    bool getIsPublic();
};
#endif // POST_H