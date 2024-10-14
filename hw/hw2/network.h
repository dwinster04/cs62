#ifndef NETWORK_H
#define NETWORK_H

#include <vector>
#include "user.h"

// class User;

class Network
{
private:
    std::vector<User*> users_; //  vector of user pointers

public:
    // default constructor

    // pre: none
    // post: create an empty object network
    Network();

    // operations

    // pre: none
    // pre: returns number of users
    int numUsers();

    // pre: user must have an id (self-explanatory)
    // post: takes an id, returns pointer to corresponding user
    User* getUser(int id);

    // pre: none
    // post: adds User to network database
    void addUser(User* user);

    // pre: friend connection must not already exist
    // post: two strings [first name] [last name] format connected/friends
    int addConnection(std::string s1, std::string s2);

    // pre: friend connection must already exist
    // post: deletes connection/friendship between the two 
    int deleteConnection(std::string s1, std::string s2);

    // pre: takes in a string [first] [last] format
    // post: returns id for that user (-1 if no user exists)
    int getId(std::string name);

    // pre: must take in a file as char* (c string)
    // post: initializes network data from file
    void readUsers(char* fname);

    // pre: must take in a file as char* (c string)
    // post: writes all network data onto a file
    void writeUsers(char* fname);

    // pre: none
    // post: remove tab from line
    std::string removeTabs(const std::string& fileLine);

    // pre: must take in id from two people
    // post: returns vector of shortest path of vertices from two input people
    std::vector<int> shortestPath(int from, int to);

    // pre: must take in from, to, and distance parameters
    // post: returns vector of IDs along the path and sets the pointer to the id of user
    std::vector<int> distanceUser(int from, int& to, int distance);

    // pre: takes in user and reference to int (score) 
    // post: returns list of users who share the highest "score" for suggested friends/highest number of common friends
    std::vector<int> suggestFriends(int who, int& score);

    // pre: none
    // post: returns a vector of vectors which are groups of connected users
    std::vector<std::vector<int> > groups();

    std::vector<int> dfshelper(User* source);

};

#endif //NETWORK_H