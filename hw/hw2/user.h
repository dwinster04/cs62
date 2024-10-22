#ifndef USER_H
#define USER_H

#include <vector>
#include <iostream>
#include <set> 
#include <string> 


class User
{ 
private:
    int id_; 
    std::string name_; 
    int year_;
    int zip_;
    std::set<int> friends_;

    // class invariants
    // 1) int id_: id stores user id 0,1,2,...
    // 2) string name_: first and last name seperated by spaces to be stored in a single string
    // 3) int year_: year stores birth year of the user
    // 4) int zip_: indicates user's zip code
    // 5) set<int> friends_: stores a list of friends for each user through adjacency lists


public: 
    // constructors

    // pre: none
    // post: creates an empty user object 
    User(); 

    //pre: none
    //post: creates a new user with user information 
    User(int id, std::string name, int year, int zip, std::set<int> friends);


    // getters 

    // pre: none
    // post: returns user id
    int getId();

    // pre: none
    // post: returns user name
    std::string getName();

    // pre: none
    // post: returns birth year of user
    int getYear(); 

    // pre: none
    // post: returns zip code of user
    int getZip(); 

    // pre: none
    // post: returns friend's list of user
    std::set<int> & getFriends();

    // pre: none
    // post: returns first name of specified user
    std::string getFirst();

    // pre: none
    // post: returns last name of specified user
    std::string getLast();


    // friend functs

    // pre: none
    // post: adds specified id to friend's list
    void addFriend(int id);

    // pre: must be an existing connection to remove
    // post: removes friend id from friend's list
    void deleteFriend(int id);

};

#endif // USER_H