#include "network.h"
#include "user.h"
#include "user.cpp"
#include <vector>
#include <set>
#include <sstream>
#include <iostream>
#include <fstream>
#include <string>

// constructor
Network::Network() {}                         // default network object auto set with size zero

// operations


int Network::numUsers()
{
    return users_.size();
}

User* Network::getUser(int id)
{
    if (id >= 0 && id < users_.size())      // check if id is within the range of accessible id's
        return users_[id];
    return nullptr;
}

void Network::addUser(User* user)
{
    if (user != nullptr)
        users_.push_back(user);               // push back user into vector
    else
        return;                               // returns if user = null ptr
}



int Network::addConnection(std::string s1, std::string s2)
{
   
    User* user1 = nullptr;                    // initialize users to nullptr
    User* user2 = nullptr;

    for (int i = 0; i <= users_.size(); ++i)
    {
        if (users_[i]->getName() == s1)       // access the data stored vector of User*'s
            {
                user1 = users_[i];            // first user found
            }
            if (users_[i]->getName() == s2)
            {
                user2 = users_[i];            // found second user
            }
    }

    if (user1 != nullptr && user2 != nullptr)
    {
        user1->addFriend(user2->getId());     // code from notes
        user2->addFriend(user1->getId());

        
        return 0;
    }

    return -1;                                // users not found
}

int Network::deleteConnection(std::string s1, std::string s2)
{
   
    User* user1 = nullptr;                    // initialize users to nullptr
    User* user2 = nullptr;

    for (int i = 0; i <= users_.size(); ++i)
    {
        if (users_[i]->getName() == s1)
            {
                user1 = users_[i]; 
            }
            if (users_[i]->getName() == s2)
            {
                user2 = users_[i]; 
            }
    }

    if (user1 != nullptr && user2 != nullptr)
    {
        user1->deleteFriend(user2->getId()); // code from notes
        user2->deleteFriend(user1->getId()); // undirected connection


        return 0;
    }

    return -1;                               // user(s) not found
}

int Network::getId(std::string name)
{
    for (int i = 0; i <= users_.size(); ++i)  
    {
        if (users_[i]->getName() == name)   // check if users_[i] == input name
            return users_[i]->getId();      // returns id of users[i]
    }
    return -1;
}

void Network::readUsers(char* name)
{
    
    std::ifstream inputFile(name);
    if (inputFile.is_open())
    {
        std::string lines;
        while (std::getline(inputFile, lines))
        {
            int id = std::stoi(lines);                     // read id as string

            std::getline(inputFile, lines);
            std::string name = lines.substr(1); // skips leading tab

            std::getline(inputFile, lines);
            int year = std::stoi(lines.substr(1)); // read year

            std::getline(inputFile, lines);
            int zip = std::stoi(lines.substr(1));  // read zip
            
            std::set<int> friends;   // initialize vector of strings to represent friends
            std::getline(inputFile, lines); 
            std::stringstream ss(lines);
            int friendId;
        
            while (ss >> friendId)
            {
                friends.insert(friendId);        // push_back vector with read friends from file
            }
        
            User* tempUser = new User(id, name, year, zip, friends);

            
            addUser(tempUser);                  // call add user function to add tempUser which holds string of read users
        }


        inputFile.close();

    }
}

void Network::writeUsers(char* fname)
{
    std::ofstream outputFile(fname);
    if (outputFile.is_open())
    {
        for (auto& user : users_)         // direct reference to user object
        {
            if (user != nullptr)
                outputFile << user->getId() << std::endl;
                outputFile << "\t" << user->getName() << std::endl;
                outputFile << user->getYear() << std::endl;
                outputFile << user->getZip() << std::endl;

                std::set<int> friends = user->getFriends(); // get friends of user and put it in their friends list
                for (auto& id : friends) // traverse through friend list
                {
                    outputFile << id << " ";
                }
                outputFile << std::endl;
        }
    }
    outputFile.close();
}