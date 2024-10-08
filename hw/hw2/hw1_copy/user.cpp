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

User::User(int id, std::string name, int year, int zip, std::set<int> friends)
{
    id_ = id;
    name_ = name; 
    year_ = year;
    zip_ = zip; 
    friends_ = friends; 
}

// getters
int User::getId()
{
    std::cout << "works" << std::endl;
    return id_; 

}

std::string User::getName()
{
    return name_; 
}

int User::getYear()
{
    return year_;
}

int User::getZip()
{
    return zip_;
}

std::set<int> & User::getFriends()
{
    return friends_;
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