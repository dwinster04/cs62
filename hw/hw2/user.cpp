#include "user.h"
#include<string>
#include<iostream>

// constructor
User::User()
{
    id = -1;
    name = " ";
    zip = -1;
    year = -1;
}

User::User(int input_id, std::string input_name, int input_year, int input_zip, std::set<int> input_friends)
{
    id = input_id;
    name = input_name; 
    year = input_year;
    zip = input_zip; 
    friends = input_friends; 
}

// getters
int User::getId()
{
    return id; 
}

std::string User::getName()
{
    return name; 
}

int User::getYear()
{
    return year;
}

int User::getZip()
{
    return zip;
}

std::set<int> & User::getFriends()
{
    return friends;
}

// friend functs
void User::addFriend(int id)
{
    for(auto i: friends)            // range based loop since elements in set are read-only
        if(i == id)                 // existing friend check
            return;                 // stops program if check is true
    friends.insert(id);             // inserts if check falls through
}

void User::deleteFriend(int id)
{
    bool check = false;             // initialize default bool to false
    
    for(auto i: friends)
        if(i == id)
            check = true;           // set bool value to true if check falls through

    if(check == true)               
        friends.erase(id);          // remove specified id from friend's list
    
    return;
}